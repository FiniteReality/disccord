#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#include "discord.h"
#include "client.h"

int main() {
	printf("Creating client...\n");
	discord_client_t* client = client_create("");
	printf("Successfully created client!\n");

	printf("Connecting...\n");
	client_connect(client);
	printf("Connected!\n");

	sleep(10);

	printf("Disconnecting...\n");
	client_disconnect(client);
	printf("Disconnected!\n");

	printf("Freeing client...\n");
	client_free(client);
	printf("Successfully freed client!\n");

	return 0;
}