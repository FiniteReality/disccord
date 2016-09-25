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
	if (token == NULL || !validateToken(token)) {
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
	/* disconnect the websocket if we are connected */
	if (client->_gateway_thread != NULL) {
		client_disconnect(client);
	}

	free(client->_token);
	free(client);
}

void *client_listen(void* arg) {
	discord_client_t* client = arg;
	client->_client_socket = websocket_create();
	websocket_connect(client->_client_socket, "wss://gateway.discord.gg");
	return NULL;
}

void client_connect(discord_client_t* client) {
	pthread_t *gateway_thread = malloc(sizeof(pthread_t));
	pthread_create(gateway_thread, NULL, client_listen, client);
	client->_gateway_thread = gateway_thread;
}

void client_disconnect(discord_client_t* client) {
	websocket_disconnect(client->_client_socket);

	/* cancel the gateway thread if it exists */
	if (client->_gateway_thread != NULL) {
		pthread_cancel(*client->_gateway_thread);
		pthread_join(*client->_gateway_thread, NULL);

		free(client->_gateway_thread);
		client->_gateway_thread = NULL;
	}

	websocket_free(client->_client_socket);
}