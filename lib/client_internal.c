#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include <cJSON/cJSON.h>

#include "models/gateway.h"
#include "client_internal.h"

/* validates a token, ensuring it has at least three "sections". */
int validateToken(const char* token) {
	return sscanf(token, "%*s.%*s.%*s");
}

void realloc_copy(char** dest, const char* src) {
	*dest = realloc(*dest, strlen(src) + 1);
	strcpy(*dest, src);
}

void* client_heartbeat_thread(void* arg) {
	discord_client_t* client = (discord_client_t*)arg;

	time_t* _heartbeat_start_time = malloc(sizeof(time_t));
	client->_heartbeat_start_time = _heartbeat_start_time;

	struct timespec ts;
	ts.tv_sec = client->_heartbeat_interval / 1000;
	ts.tv_nsec = (client->_heartbeat_interval % 1000) * 1000000;

	cJSON* root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "op", OP_HEARTBEAT);
	cJSON_AddNumberToObject(root, "d", client->_seq);

	for(;;) {
		/* heartbeat_interval is in ms*/
		nanosleep(&ts, NULL);
		cJSON_SetIntValue(root, client->_seq);

		char* data = cJSON_Print(root);
		size_t len = strlen(data);

		printf("Sending %zu bytes for heartbeat\n", len);
		time(_heartbeat_start_time);
		if (websocket_send(client->_client_socket, data, len, 0) > 0)
			client->_seq++;

		free(data);
	}

	cJSON_Delete(root);
	free(root);

	return NULL;
}

int client_receive_callback(client_websocket_t* socket, char* data, size_t length) {
	discord_client_t* client = (discord_client_t*)websocket_get_userdata(socket);

	printf("Received data: %s\n", data);

	/* TODO: handle this */
	cJSON* root = cJSON_Parse(data);

	if (root) {
		cJSON* op = cJSON_GetObjectItem(root, "op");
		cJSON* d = cJSON_GetObjectItem(root, "d");
		if (op && op->valueint) {
			enum GATEWAY_OPCODE opcode = (enum GATEWAY_OPCODE)(op->valueint);
			switch (opcode) {
				case OP_HELLO:
				{
					printf("Handling OP_HELLO\n");
					cJSON* _heartbeat_interval = cJSON_GetObjectItem(d, "heartbeat_interval");

					if (_heartbeat_interval) {
						client->_heartbeat_interval = _heartbeat_interval->valueint;
						printf("New heartbeat interval: %i\n", client->_heartbeat_interval);

						pthread_t* heartbeat_thread = malloc(sizeof(pthread_t));
						pthread_create(heartbeat_thread, NULL, client_heartbeat_thread, client);
						client->_heartbeat_thread = heartbeat_thread;
					}

					break;
				}
				case OP_HEARTBEAT_ACK:
				{
					/* TODO: latency update */
					time_t now = time(NULL);
					double diff = difftime(*(client->_heartbeat_start_time), now);
					printf("Latency: %e\n\n", diff);
					break;
				}
				default:
					printf("Unhandled opcode: %u\n", opcode);
			}
		}
	}

	return 0;
}