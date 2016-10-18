#ifndef _websocket_h_
#define _websocket_h_

#include <libwebsockets.h>
#include <pthread.h>

#include "discord.h"

typedef struct websocket_callbacks client_websocket_callbacks_t;
typedef struct websocket_client client_websocket_t;

typedef int (*websocket_receive_callback)(client_websocket_t* client, char* data, size_t length);
typedef int (*websocket_connection_error_callback)(client_websocket_t* client, char* reason, size_t length);

struct websocket_callbacks {
	websocket_receive_callback on_receive;
	websocket_connection_error_callback on_connection_error;
};

struct websocket_client {
	client_websocket_callbacks_t* _callbacks;
	struct lws_context* _context;
	struct lws* _wsi;

	char* _address;
	char* _path;

	char* _current_packet;
	size_t _current_packet_length;

	uint8_t _remain_connected;
	uint8_t _connected;
	/*uint8_t _disconnect; */

	void* _userdata;

	pthread_mutex_t* _write_mutex;
};

client_websocket_t* websocket_create(client_websocket_callbacks_t* callbacks);

void* websocket_set_userdata(client_websocket_t* client, void* userdata);
void* websocket_get_userdata(client_websocket_t* client);

void websocket_free(client_websocket_t* client);
void websocket_connect(client_websocket_t* client, const char* address);
void websocket_disconnect(client_websocket_t* client);
void websocket_think(client_websocket_t* websocket);

int websocket_send(client_websocket_t* client, char* data, size_t len, int mode);

#endif /* _websocket_h_ */