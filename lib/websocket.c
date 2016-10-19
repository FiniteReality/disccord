#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "websocket.h"
#include "websocket_internal.h"

static struct lws_protocols protocols[] = {
	{ "discord-protocol", discord_protocol, 0, 1024, 0, NULL },
	{ NULL, NULL, 0, 0, 0, NULL } /* end */
};

static struct lws_extension exts[] = {
	{ 
		"permessage-deflate",
		lws_extension_callback_pm_deflate,
		"permessage-deflate; client_no_context_takeover; client_max_window_bits"
	},
	{
		"deflate-frame",
		lws_extension_callback_pm_deflate,
		"deflate_frame"
	},
	{ NULL, NULL, NULL } /* end */
};

client_websocket_t* websocket_create(client_websocket_callbacks_t* callbacks) {
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.gid = -1;
	info.uid = -1;
	info.protocols = protocols;
	info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

	client_websocket_t *client = malloc(sizeof(client_websocket_t));
	info.user = client;
	
	struct lws_context* context = lws_create_context(&info);
	client->_context = context;
	client->_remain_connected = 0;
	client->_callbacks = callbacks;

	client->_write_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(client->_write_mutex, NULL);

	return client;
}

void* websocket_set_userdata(client_websocket_t* client, void* userdata) {
	void* old = client->_userdata;
	client->_userdata = userdata;
	return old;
}

void* websocket_get_userdata(client_websocket_t* client) {
	return client->_userdata;
}

void websocket_free(client_websocket_t* client) {
	if (client->_remain_connected) {
		websocket_disconnect(client);
	}

	/* free the context */
	lws_context_destroy(client->_context);
	ERR_remove_thread_state(NULL);

	/* clean up mutexes */
	pthread_mutex_destroy(client->_write_mutex);

	/* free alloc'd data */
	free(client->_address);
	free(client->_path);
	free(client->_write_mutex);
	free(client);
}

void websocket_connect(client_websocket_t* client, const char* address) {
	struct lws_client_connect_info info;
	memset(&info, 0, sizeof(info));

	info.context = client->_context;
	info.ssl_connection = 1;
	info.userdata = client;

	size_t s = strlen(address);
	client->_address = malloc(s + 1);
	memcpy(client->_address, address, s);

	const char* prot;
	const char* path;

	if (lws_parse_uri(client->_address, &prot, &info.address, &info.port, &path))
		return;

	s = strlen(path);
	client->_path = malloc(s + 2);
	client->_path[0] = '/';
	memcpy(client->_path + 1, path, s);

	info.path = client->_path;
	info.host = info.address;
	info.origin = info.address;
	info.ietf_version_or_minus_one = -1;
	info.client_exts = exts;

	printf("protocol: %s\naddress: %s\nport: %i\npath: %s\nhost: %s\norigin: %s\n", prot, info.address, info.port, info.path, info.host, info.origin);

	client->_remain_connected = 1;

	client->_wsi = lws_client_connect_via_info(&info);
	client->_connected = 1;
}

void websocket_disconnect(client_websocket_t* client) {
	lws_cancel_service(client->_context);
	//client->_disconnect = 1;
}

void websocket_think(client_websocket_t* client) {
	lws_service(client->_context, 500);
}


int websocket_send(client_websocket_t* client, char* data, size_t len, int mode) {
	pthread_mutex_lock(client->_write_mutex);
	/* it is safe to write at this point */

	unsigned char cdata[LWS_PRE + len];
	memcpy(&cdata[LWS_PRE], data, len);

	unsigned char* ptr = &cdata[LWS_PRE];

	int status;
	switch (mode) {
		case 1:
			status = lws_write(client->_wsi, ptr, len, LWS_WRITE_BINARY);
			break;
		case 2:
			status = lws_write(client->_wsi, ptr, len, LWS_WRITE_PING);
			break;
		case 0:
		default:
			status = lws_write(client->_wsi, ptr, len, LWS_WRITE_TEXT);
			break;
	}

	/* ensure we unlock the mutex to prevent deadlocks */
	pthread_mutex_unlock(client->_write_mutex);

	return status;
}