#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "client.h"

/* validates a token, ensuring it has at least three "sections". */
int validateToken(const char* token) {
	return sscanf(token, "%*s.%*s.%*s");
}

void realloc_copy(char** dest, const char* src) {
	*dest = realloc(*dest, strlen(src) + 1);
	strcpy(*dest, src);
}


discord_client_t* client_create(const char* token) {
	if (!validateToken(token)) {
		/* invalid token */
		return NULL;
	}

	discord_client_t* client = malloc(sizeof(discord_client_t));
	client->_token = NULL;
	client->_gateway_thread = NULL;

	realloc_copy(&client->_token, token);

	/* TODO: this */
	return client;
}

void client_free(discord_client_t* client) {
	/* do not try to free if we haven't tried to connect yet */
	if (client->_gateway_thread != NULL) {
		pthread_cancel(*client->_gateway_thread);
		pthread_join(client->_gateway_thread, NULL);
	}

	free(client->_token);
	free(client);
}

void client_connect(discord_client_t* client) {

}