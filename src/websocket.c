#include <stdlib.h>
#include <string.h>

#include "websocket.h"

client_websocket_t* websocket_create() {
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.gid = -1;
	info.uid = -1;

	client_websocket_t *client = malloc(sizeof(client_websocket_t));
	
	struct lws_context* context = lws_create_context(&info);
	client->_context = context;
	client->_connect = 0;

	return client;
}

void websocket_free(client_websocket_t* client) {
	if (client->_connect) {
		websocket_disconnect(client);
		lws_context_destroy(client->_context);
	}

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

	free(address_internal);

	lws_client_connect_via_info(&info);
	client->_connect = 1;

	while (client->_connect) {
		lws_service(client->_context, 500);
	}
}

void websocket_disconnect(client_websocket_t* client) {
	client->_connect = 0;
}