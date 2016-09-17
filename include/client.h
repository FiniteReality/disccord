#ifndef _client_h_
#define _client_h_

#include "discord.h"

typedef struct {
	const char* _token;
	/* TODO: fill this out with stuff */
	int _gateway_thread_id;
} discord_client_t;

LIB_EXPORT discord_client_t *create_client(const char* token);

#endif /* _client_h_ */