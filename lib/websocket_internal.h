#ifndef _websocket_internal_h_
#define _websocket_internal_h_

#include <pthread.h>
#include <arpa/inet.h>

#include <openssl/ssl.h>


int discord_protocol(struct lws* wsi, enum lws_callback_reasons reason,
		void* user, void* in, size_t len);

static struct lws_protocols protocols[] = {
	{ "discord-protocol", discord_protocol, 0, 1024 },
	{ NULL, NULL, NULL, NULL } /* end */
};

static struct lws_extension exts[] = {
	{ 
		"permessage-deflate",
		lws_extension_callback_pm_deflate,
		"permessage-deflate; client_no_context_takeover; client_max_window_bits"
	},
	{
		"deflate-frame",
		lws_extension_callback_pm_deflate,
		"deflate_frame"
	},
	{ NULL, NULL, NULL } /* end */
};

#endif /* _websocket_internal_h_ */