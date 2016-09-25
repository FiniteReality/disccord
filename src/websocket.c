#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <openssl/ssl.h>
#include <pthread.h>

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
	printf("Callback %s (%i)\n", callback_reasons[reason], reason);
	switch (reason) {
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
			if (in != NULL && len > 0) {
				printf("Connection error: (%zu) %s\n", len, (char*)in);
			} else {
				printf("Unknown connection error\n");
			}
			break;
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			printf("Connection established\n");
			break;
		case LWS_CALLBACK_CLOSED:
			printf("Session closed\n");
			break;
		case LWS_CALLBACK_RECEIVE:
			lws_callback_on_writable(wsi);
		case LWS_CALLBACK_CLIENT_RECEIVE:
			((char*)in)[len] = '\0';
			printf("Received data: %zu bytes\n%s\n", len, (char*)in);
			break;
		case LWS_CALLBACK_GET_THREAD_ID:
			return pthread_self();
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
			return 1;
		default:
			break;
	}

	return 0;
}

static struct lws_protocols protocols[] = {
	{ "test-protocol", callback_test_protocol, 0, 20 },
	{ NULL, NULL, 0, 0 } /* end */
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

client_websocket_t* websocket_create() {
	lws_set_log_level(1023, NULL); // bitwise OR of all of the LLL_ constants
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.gid = -1;
	info.uid = -1;
	info.protocols = protocols;
	info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

	client_websocket_t *client = malloc(sizeof(client_websocket_t));
	
	struct lws_context* context = lws_create_context(&info);
	client->_context = context;
	client->_connect = 0;

	return client;
}

void websocket_free(client_websocket_t* client) {
	if (client->_connect) {
		websocket_disconnect(client);
	}

	/* free the context */
	lws_context_destroy(client->_context);

	free(client);
}

void websocket_connect(client_websocket_t* client, const char* address) {
	struct lws_client_connect_info info;
	memset(&info, 0, sizeof(info));

	info.context = client->_context;
	info.ssl_connection = 1;

	char* address_internal = malloc(strlen(address) + 1);
	memcpy(address_internal, address, strlen(address));

	const char* prot;

	if (lws_parse_uri(address_internal, &prot, &info.address, &info.port, &info.path))
		return;

	info.host = info.address;
	info.origin = info.address;
	info.ietf_version_or_minus_one = -1;
	info.client_exts = exts;

	printf("protocol: %s\naddress: %s\nport: %i\npath: %s\nhost: %s\norigin: %s\n", prot, info.address, info.port, info.path, info.host, info.origin);

	free(address_internal);

	lws_client_connect_via_info(&info);
	client->_connect = 1;

	while (client->_connect) {
		lws_service(client->_context, 20);
	}
}

void websocket_disconnect(client_websocket_t* client) {
	client->_connect = 0;
}