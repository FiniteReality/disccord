#ifndef _websocket_h_
#define _websocket_h_

#include <libwebsockets.h>

#include "discord.h"

typedef struct websocket_callbacks client_websocket_callbacks;
typedef struct websocket_client client_websocket_t;

typedef int (*websocket_receive_callback)(client_websocket_t* client, char* data, size_t length);

struct websocket_callbacks {
	websocket_receive_callback on_receive;
};

struct websocket_client {
	client_websocket_callbacks* _callbacks;
	struct lws_context* _context;

	char* _address;
	char* _path;

	uint8_t _remain_connected;
	uint8_t _connected;

	void* _userdata;
};

client_websocket_t* websocket_create(client_websocket_callbacks* callbacks);

void* websocket_set_userdata(client_websocket_t* client, void* userdata);
void* websocket_get_userdata(client_websocket_t* client);

void websocket_free(client_websocket_t* client);
void websocket_connect(client_websocket_t* client, const char* address);
void websocket_disconnect(client_websocket_t* client);

#endif /* _websocket_h_ */