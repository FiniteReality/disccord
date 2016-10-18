#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#include "discord.h"
#include "client.h"
#include "message.h"

int client_message_received(discord_client_t* client, message_t* message) {
	printf("\nMessage received: %s\n", message->_contents); /* TODO: provide better methods for this */
	if (strstr(message->_contents, "!ping") == message->_contents) {
		printf("Received ping command!\n");

		char data[256];
		sprintf(data, "Hello, world, from C!\nUsing %s at <%s>!", DISCCORD_VERSION_STRING, DISCCORD_PROJECT_URL);

		printf("Sending %s\n", data);

		client_send_message(client, message->_channel_id, data);
	}
	return 0;
}

int main() {

	FILE* fp = fopen("token.data.txt", "r");

	if (!fp) {
		perror("fopen");
		return 1;
	}

	char token[128];
	fgets(token, 128, fp);
	fclose(fp);

	disccord_init();

	discord_client_callbacks_t callbacks;
	callbacks.on_message_receive = client_message_received;

	printf("Creating client...\n");
	discord_client_t* client = client_create(&callbacks, token);
	if (client) {
		printf("Successfully created client!\n");
	} else {
		fprintf(stderr, "Failed to create discord client!\n");
		return 1;
	}

	printf("Connecting...\n");
	client_connect(client);

	sleep(120);

	printf("Disconnecting...\n");
	client_disconnect(client);

	sleep(3); /* ensure there's enough time to disconnect cleanly */

	printf("Freeing client...\n");
	client_free(client);
	printf("Successfully freed client!\n");

	disccord_cleanup();
	return 0;
}