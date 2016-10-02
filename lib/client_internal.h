#ifndef _CLIENT_INTERNAL_H_
#define _CLIENT_INTERNAL_H_

#include "client.h"

int validateToken(const char* token);
void realloc_copy(char** dest, const char* src);

int client_receive_callback(client_websocket_t* socket, char* data, size_t length);
int client_connection_error_callback(client_websocket_t* socket, char* data, size_t length);

#endif /* _CLIENT_INTERNAL_H_ */