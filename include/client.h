#ifndef _client_h_
#define _client_h_

#include <pthread.h>

#include "discord.h"

typedef struct {
	const char* _token;
	/* TODO: fill this out with stuff */
	pthread_t *_gateway_thread;
} discord_client_t;

LIB_EXPORT discord_client_t* client_create(const char* token);
LIB_EXPORT void client_free(discord_client_t* client);

LIB_EXPORT void client_connect(discord_client_t* client);
LIB_EXPORT void client_disconnect(discord_client_t* client);

#endif /* _client_h_ */