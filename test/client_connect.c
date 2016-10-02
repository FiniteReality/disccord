#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#include "discord.h"
#include "client.h"

int main() {

	FILE* fp = fopen("token.data.txt", "r");

	if (!fp) {
		perror("fopen");
		return 0;
	}

	char token[128];
	fgets(token, 128, fp);
	fclose(fp);

	disccord_init();

	printf("Creating client...\n");
	discord_client_t* client = client_create(token);
	printf("Successfully created client!\n");

	printf("Connecting...\n");
	client_connect(client);
	printf("Connected!\n");

	sleep(120);

	printf("Disconnecting...\n");
	client_disconnect(client);
	printf("Disconnected!\n");

	printf("Freeing client...\n");
	client_free(client);
	printf("Successfully freed client!\n");

	disccord_cleanup();
	return 0;
}