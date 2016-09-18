#ifndef _websocket_h_
#define _websocket_h_

#include <libwebsockets.h>

typedef struct {
	struct lws_context* context;
} client_websocket_t;

client_websocket_t* websocket_create();

void websocket_connect(client_websocket_t* client, const char* address);

#endif /* _websocket_h_ */