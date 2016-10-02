#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <arpa/inet.h>

#include <openssl/ssl.h>

#include "websocket.h"

/* This is here purely for debugging reasons. */
static char* callback_reasons[] = {
	"LWS_CALLBACK_ESTABLISHED",
	"LWS_CALLBACK_CLIENT_CONNECTION_ERROR",
	"LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH",
	"LWS_CALLBACK_CLIENT_ESTABLISHED",
	"LWS_CALLBACK_CLOSED",
	"LWS_CALLBACK_CLOSED_HTTP",
	"LWS_CALLBACK_RECEIVE",
	"LWS_CALLBACK_RECEIVE_PONG",
	"LWS_CALLBACK_CLIENT_RECEIVE",
	"LWS_CALLBACK_CLIENT_RECEIVE_PONG",
	"LWS_CALLBACK_CLIENT_WRITEABLE",
	"LWS_CALLBACK_SERVER_WRITEABLE",
	"LWS_CALLBACK_HTTP",
	"LWS_CALLBACK_HTTP_BODY",
	"LWS_CALLBACK_HTTP_BODY_COMPLETION",
	"LWS_CALLBACK_FILE_COMPLETION",
	"LWS_CALLBACK_HTTP_WRITEABLE",
	"LWS_CALLBACK_FILTER_NETWORK_CONNECTION",
	"LWS_CALLBACK_FILTER_HTTP_CONNECTION",
	"LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED",
	"LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION",
	"LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS",
	"LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS",
	"LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION",
	"LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER",
	"LWS_CALLBACK_CONFIRM_EXTENSION_OKAY",
	"LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED",
	"LWS_CALLBACK_PROTOCOL_INIT",
	"LWS_CALLBACK_PROTOCOL_DESTROY",
	"LWS_CALLBACK_WSI_CREATE",
	"LWS_CALLBACK_WSI_DESTROY",
	"LWS_CALLBACK_GET_THREAD_ID",
	"LWS_CALLBACK_ADD_POLL_FD",
	"LWS_CALLBACK_DEL_POLL_FD",
	"LWS_CALLBACK_CHANGE_MODE_POLL_FD",
	"LWS_CALLBACK_LOCK_POLL",
	"LWS_CALLBACK_UNLOCK_POLL",
	"LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY",
	"LWS_CALLBACK_WS_PEER_INITIATED_CLOSE",
	"LWS_CALLBACK_WS_EXT_DEFAULTS",
	"LWS_CALLBACK_CGI",
	"LWS_CALLBACK_CGI_TERMINATED",
	"LWS_CALLBACK_CGI_STDIN_DATA",
	"LWS_CALLBACK_CGI_STDIN_COMPLETED",
	"LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP",
	"LWS_CALLBACK_CLOSED_CLIENT_HTTP",
	"LWS_CALLBACK_RECEIVE_CLIENT_HTTP",
	"LWS_CALLBACK_COMPLETED_CLIENT_HTTP",
	"LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ"
};

static int callback_test_protocol(struct lws* wsi, enum lws_callback_reasons reason,
		void* user, void* in, size_t len)
{
	client_websocket_t* client = (client_websocket_t*)user;
	printf("Callback %s (%i)\n", callback_reasons[reason], reason);
	switch (reason) {
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		{
			if (client->_callbacks->on_connection_error) {
				if (in && len)
					client->_callbacks->on_connection_error(client, (char*)in, len);
				else
					client->_callbacks->on_connection_error(client, "Unknown", 7);
			}

			client->_connected = 0;
			break;
		}
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
		{
			break;
		}
		case LWS_CALLBACK_CLOSED:
		{
			break;
		}
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
		{
			uint16_t close_reason = ntohs(*(uint16_t*)in);

			char buffer[50];
			size_t len = sprintf(buffer, "Server sent close %hu", close_reason);

			client->_callbacks->on_connection_error(client, buffer, len);

			break;
		}
		case LWS_CALLBACK_CLIENT_RECEIVE:
		{
			char* data = (char*)in;
			data[len] = '\0';

			if (client->_callbacks->on_receive)
				return client->_callbacks->on_receive(client, data, len);

			break;
		}
		case LWS_CALLBACK_GET_THREAD_ID:
		{
			return pthread_self();
		}
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
		{
			return 1;
		}
		default:
		{
			break;
		}
	}

	return 0;
}

static struct lws_protocols protocols[] = {
	{ "test-protocol", callback_test_protocol, 0, 1024 },
	{ NULL, NULL, NULL, NULL } /* end */
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
	lws_set_log_level(1023 ^ LLL_PARSER ^ LLL_EXT, NULL); // bitwise OR of all of the LLL_ constants
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

	while (client->_remain_connected) {
		if (!client->_connected) {
			client->_wsi = lws_client_connect_via_info(&info);
			client->_connected = 1;
		}
		lws_service(client->_context, 500);
	}
}

void websocket_disconnect(client_websocket_t* client) {
	client->_remain_connected = 0;
}

int websocket_send(client_websocket_t* client, char* data, size_t len, int mode) {
	pthread_mutex_lock(client->_write_mutex);
	/* it is safe to write at this point */

	int status;
	switch (mode) {
		case 1:
			status = lws_write(client->_wsi, data, len, LWS_WRITE_BINARY);
			break;
		case 2:
			status = lws_write(client->_wsi, data, len, LWS_WRITE_PING);
			break;
		case 0:
		default:
			status = lws_write(client->_wsi, data, len, LWS_WRITE_TEXT);
			break;
	}

	/* ensure we unlock the mutex to prevent deadlocks */
	pthread_mutex_unlock(client->_write_mutex);

	return status;
}