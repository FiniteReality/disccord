#ifndef _websocket_h_
#define _websocket_h_

#include <libwebsockets.h>

#include "discord.h"

typedef struct {
	struct lws_context* _context;
	char* _address;
	int _connect;
} client_websocket_t;

LIB_EXPORT client_websocket_t* websocket_create();
LIB_EXPORT void websocket_free(client_websocket_t* client);

LIB_EXPORT void websocket_connect(client_websocket_t* client, const char* address);

LIB_EXPORT void websocket_disconnect(client_websocket_t* client);

#endif /* _websocket_h_ */