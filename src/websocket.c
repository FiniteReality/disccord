#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "websocket.h"

static int callback_test_protocol(struct lws* wsi, enum lws_callback_reasons reason,
		void* user, void* in, size_t len)
{
	switch (reason) {
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			printf("Client established\n");
			break;
		case LWS_CALLBACK_ESTABLISHED:
			printf("Client connection established\n");
			break;
		case LWS_CALLBACK_CLOSED:
			printf("Session closed\n");
			break;
		case LWS_CALLBACK_RECEIVE:
		case LWS_CALLBACK_CLIENT_RECEIVE:
			printf("Data received\n");
			break;
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
			printf("Connection error\n");
			break;
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
			printf("Confirm extension\n");
			break;
		case LWS_CALLBACK_RECEIVE_CLIENT_HTTP:
			printf("Receive client HTTP\n");
			break;
		case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
			printf("Completed client HTTP\n");
			break;
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:
			printf("Verify certs\n");
			break;
		default:
			printf("Unknown callback %i\n", reason);
			break;
	}

	return 0;
}

static struct lws_protocols protocols[] = {
	{ "test-protocol", callback_test_protocol, 0, 20 },
	{ NULL, NULL, 0, 0 } /* end */
};

static struct lws_extension exts[] = {
	{ NULL, NULL, NULL }
};


client_websocket_t* websocket_create() {
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.gid = -1;
	info.uid = -1;
	info.protocols = protocols;

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

	lws_context_destroy(client->_context);

	free(client);
}

void websocket_connect(client_websocket_t* client, const char* address) {
	struct lws_client_connect_info info;

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

	free(address_internal);
	free(prot);

	lws_client_connect_via_info(&info);
	client->_connect = 1;

	while (client->_connect) {
		lws_service(client->_context, 500);
	}
}

void websocket_disconnect(client_websocket_t* client) {
	client->_connect = 0;
}