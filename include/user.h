#ifndef _user_h_
#define _user_h_

#include <stdint.h>

#include "client.h"

typedef struct {
	uint64_t _user_id;
	uint16_t _discriminator;
	const char* _name;
	uint32_t _name_len;
	discord_client_t* _client;
} user_info_t;

LIB_EXPORT const char* get_user_name(user_info_t* user, int* length);
LIB_EXPORT uint64_t get_user_id(user_info_t* user);
LIB_EXPORT uint16_t get_user_discrim(user_info_t* user);

LIB_EXPORT user_info_t *get_user_info(discord_client_t* client, uint64_t id);

#endif /* _user_h_ */