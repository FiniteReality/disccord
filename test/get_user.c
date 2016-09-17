#include <stdio.h>
#include <stdint.h>

#include "discord.h"
#include "client.h"
#include "user.h"

/* ./get_user token id */

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "usage: get_user token id\n");
		return 1;
	}

	const char* token = argv[1];
	const char* user_id_str = argv[2];

	uint64_t user_id;

	if (!sscanf(user_id_str, "%lu", &user_id)) {
		fprintf(stderr, "get_user: invalid user id");
		return 2;
	}

	discord_client_t* client = create_client(token);
	user_info_t* user = get_user_info(client, user_id);
	const char* name = get_user_name(user, NULL);
	uint16_t discrim = get_user_discrim(user);
	printf("Found user with id %lu: %s#%u\n", user_id, name, discrim);
	return 0;
}