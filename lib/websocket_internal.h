#ifndef _websocket_internal_h_
#define _websocket_internal_h_

#include <pthread.h>
#include <arpa/inet.h>

#include <openssl/ssl.h>


int discord_protocol(struct lws* wsi, enum lws_callback_reasons reason,
		void* user, void* in, size_t len);

#endif /* _websocket_internal_h_ */