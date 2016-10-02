#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include <cJSON/cJSON.h>

#include "models/gateway.h"
#include "client_internal.h"

#include "models/dispatches.h"

/* validates a token, ensuring it has at least three "sections". */
int validateToken(const char* token) {
	return sscanf(token, "%*s.%*s.%*s");
}

void realloc_copy(char** dest, const char* src) {
	*dest = realloc(*dest, strlen(src) + 1);
	strcpy(*dest, src);
}

void timespec_diff(struct timespec *start, struct timespec *stop, struct timespec *result)
{
	if ((stop->tv_nsec - start->tv_nsec) < 0) {
		result->tv_sec = stop->tv_sec - start->tv_sec - 1;
		result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
	} else {
		result->tv_sec = stop->tv_sec - start->tv_sec;
		result->tv_nsec = stop->tv_nsec - start->tv_nsec;
	}

	return;
}


void client_send_identify(discord_client_t* client) {
	printf("Sending IDENTIFY\n");
	cJSON* root = cJSON_CreateObject();
	cJSON* data;
	cJSON* data_properties;

	cJSON_AddNumberToObject(root, "op", OP_IDENTIFY);
	cJSON_AddItemToObject(root, "d", data = cJSON_CreateObject());
		cJSON_AddStringToObject(data, "token", client->_token);
		cJSON_AddItemToObject(data, "properties", data_properties = cJSON_CreateObject());
			cJSON_AddStringToObject(data_properties, "$browser", DISCCORD_VERSION_STRING);
		cJSON_AddNumberToObject(data, "large_threshold", 50);
	cJSON_AddBoolToObject(data, "compress", 0); /* TODO: compression support */

	char* packet = cJSON_PrintUnformatted(root);
	size_t len = strlen(packet);

	if (websocket_send(client->_client_socket, packet, len, 0) < 0) {
		/* TODO: handle errors */
	}

	cJSON_Delete(root);
}


void* client_heartbeat_thread(void* arg) {
	discord_client_t* client = (discord_client_t*)arg;

	struct timespec* heartbeat_time = malloc(sizeof(struct timespec));
	client->_heartbeat_start = heartbeat_time;

	struct timespec ts;
	ts.tv_sec = client->_heartbeat_interval / 1000;
	ts.tv_nsec = (client->_heartbeat_interval % 1000) * 1000000;

	cJSON* root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "op", OP_HEARTBEAT);
	cJSON_AddNumberToObject(root, "d", client->_seq);

	while(client->_send_heartbeats) {
		/* heartbeat_interval is in ms*/
		nanosleep(&ts, NULL);
		cJSON_SetIntValue(root, client->_seq);

		char* data = cJSON_PrintUnformatted(root);
		size_t len = strlen(data);

		printf("Sending %zu bytes for heartbeat\n", len);
		timespec_get(heartbeat_time, TIME_UTC);
		if (websocket_send(client->_client_socket, data, len, 0) > 0)
			client->_seq++;

		free(data);
	}

	cJSON_Delete(root);
	free(client->_heartbeat_start);
	client->_heartbeat_start = NULL;

	return NULL;
}

void client_handle_dispatch(discord_client_t* client, const enum DISPATCH_TYPE dispatch, char* dispatch_str, cJSON* root) {
	cJSON* d = cJSON_GetObjectItem(root, "d");
	switch (dispatch) {
		case DISPATCH_READY:
		{
			break;
		}
		case DISPATCH_MESSAGE_CREATE:
		{
			char* message_id = cJSON_GetObjectItem(d, "id")->valuestring;
			char* content = cJSON_GetObjectItem(d, "content")->valuestring;
			printf("Received message %s with contents '%s'\n", message_id, content);
			break;
		}
		default:
			printf("Unhandled dispatch: %s\n", dispatch_str);
	}
}

int client_receive_callback(client_websocket_t* socket, char* data, size_t length) {
	discord_client_t* client = (discord_client_t*)websocket_get_userdata(socket);

	//printf("Received data: %s\n", data);

	/* TODO: handle this */
	cJSON* root = cJSON_Parse(data);

	if (root) {
		cJSON* op = cJSON_GetObjectItem(root, "op");
		if (op) {
			enum GATEWAY_OPCODE opcode = (enum GATEWAY_OPCODE)(op->valueint);
			switch (opcode) {
				case OP_DISPATCH:
				{
					cJSON* _dispatch_type = cJSON_GetObjectItem(root, "t");

					if (_dispatch_type && _dispatch_type->valuestring) {
						char* dispatch_type = _dispatch_type->valuestring;

						const struct DISPATCH_HASH* _dispatch = in_word_set(dispatch_type, strlen(dispatch_type));
						const enum DISPATCH_TYPE dispatch = _dispatch->value;

						client_handle_dispatch(client, dispatch, dispatch_type, root);
					}
					break;
				}
				case OP_HELLO:
				{
					cJSON* d = cJSON_GetObjectItem(root, "d");
					cJSON* _heartbeat_interval = cJSON_GetObjectItem(d, "heartbeat_interval");

					if (_heartbeat_interval) {
						client->_heartbeat_interval = _heartbeat_interval->valueint;
						printf("New heartbeat interval: %i\n", client->_heartbeat_interval);
						client->_send_heartbeats = 1;

						pthread_t* heartbeat_thread = malloc(sizeof(pthread_t));
						pthread_create(heartbeat_thread, NULL, client_heartbeat_thread, client);
						client->_heartbeat_thread = heartbeat_thread;
					}

					client_send_identify(client);

					break;
				}
				case OP_HEARTBEAT_ACK:
				{
					struct timespec now, diff;

					timespec_get(&now, TIME_UTC);
					timespec_diff(client->_heartbeat_start, &now, &diff);
					double latency = (double)diff.tv_sec + 1.0e-9*diff.tv_nsec;

					printf("Latency: %fms\n\n", latency * 1000);
					break;
				}
				default:
					printf("Unhandled opcode: %u\n", opcode);
			}
		}
	}

	cJSON_Delete(root);

	return 0;
}

int client_connection_error_callback(client_websocket_t* socket, char* reason, size_t length) {
	discord_client_t* client = (discord_client_t*)websocket_get_userdata(socket);

	printf("Connection error: %s (%u)\n", reason, length);

	client_disconnect(client);
}