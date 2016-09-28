#include <stdint.h>
#include <stdio.h>

#include "discord.h"
#include "client.h"

int main() {
	disccord_init();

	printf("Creating client...\n");
	discord_client_t* client = client_create("");
	printf("Successfully created client!\n");

	printf("Freeing client...\n");
	client_free(client);
	printf("Successfully freed client!\n");

	disccord_cleanup();
	return 0;
}