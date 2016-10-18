#ifndef _client_h_
#define _client_h_

#include <pthread.h>
#include <time.h>
#include <curl/curl.h>

typedef struct discord_client discord_client_t;

#include "websocket.h"
#include "message.h"
#include "discord.h"

typedef int (*client_message_receive_callback)(discord_client_t* client, message_t* message);

typedef struct {
	client_message_receive_callback on_message_receive;
} discord_client_callbacks_t;

struct discord_client {
	char* _token;

	int _heartbeat_interval;
	int _seq;
	struct timespec* _heartbeat_start;
	uint8_t _send_heartbeats;

	CURLM* _curl_handle;
	pthread_t* _heartbeat_thread;
	pthread_t* _gateway_thread;

	client_websocket_t* _client_socket;
	discord_client_callbacks_t* _callbacks;
};

LIB_EXPORT discord_client_t* client_create(discord_client_callbacks_t* callbacks, const char* token);
LIB_EXPORT void client_free(discord_client_t* client);

LIB_EXPORT void client_connect(discord_client_t* client);
LIB_EXPORT void client_disconnect(discord_client_t* client);

LIB_EXPORT void client_send_message(discord_client_t* client, uint64_t channel_id, const char* contents);

#endif /* _client_h_ */