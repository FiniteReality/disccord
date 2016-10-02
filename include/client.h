#ifndef _client_h_
#define _client_h_

#include <pthread.h>
#include <time.h>

#include "websocket.h"
#include "discord.h"

typedef struct {
	char* _token;

	int _heartbeat_interval;
	int _seq;
	struct timespec* _heartbeat_start;
	uint8_t _send_heartbeats;

	pthread_t* _heartbeat_thread;
	pthread_t* _gateway_thread;

	client_websocket_t* _client_socket; 
} discord_client_t;

LIB_EXPORT discord_client_t* client_create(const char* token);
LIB_EXPORT void client_free(discord_client_t* client);

LIB_EXPORT void client_connect(discord_client_t* client);
LIB_EXPORT void client_disconnect(discord_client_t* client);

#endif /* _client_h_ */