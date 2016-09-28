#ifndef _websocket_h_
#define _websocket_h_

#include <libwebsockets.h>

#include "discord.h"

#define MAX_CONNECT_ATTEMPTS 3

typedef struct {
	struct lws_context* _context;
	char* _address;
	char* _path;
	uint8_t _remain_connected;
	uint8_t _connected;
	uint8_t _connection_attempts;
} client_websocket_t;

client_websocket_t* websocket_create(struct lws_context* parent);
void websocket_free(client_websocket_t* client);

void websocket_connect(client_websocket_t* client, const char* address);

void websocket_disconnect(client_websocket_t* client);

#endif /* _websocket_h_ */