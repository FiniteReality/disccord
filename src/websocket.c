#include <stdlib.h>
#include <string.h>

#include "websocket.h"

client_websocket_t* websocket_create(){
	struct lws_context_creation_info info;
	info.port = CONTEXT_PORT_NO_LISTEN;

	client_websocket_t *client = malloc(sizeof(client_websocket_t));
	
	struct lws_context* context = lws_create_context(&info);
	client->context = context;

	return client;
}

void websocket_connect(client_websocket_t* client, const char* address) {
	struct lws_client_connect_info info;
	info.context = client->context;

	char* address_internal = malloc(strlen(address) + 1);
	memcpy(address_internal, address, strlen(address));

	const char* prot, path;

	lws_parse_uri(address_internal, &prot, &info.address, &info.port, &path);

	free(address_internal);
}