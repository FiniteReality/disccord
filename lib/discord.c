#include <openssl/ssl.h>

#include "discord.h"

/* Initializes disccord, calling all prerequesite functions. */
void disccord_init() {
	/* no-op as of right now */
}

/* Cleans up all resources created by disccord */
void disccord_cleanup() {
	ERR_remove_thread_state(NULL);

	EVP_cleanup();
	ERR_free_strings();
	CRYPTO_cleanup_all_ex_data();
	ENGINE_cleanup();
	CONF_modules_unload(1);
	CONF_modules_free();
	COMP_zlib_cleanup();
	/* TODO: figure out what ssl define this is behind */
	/* SSL_COMP_free_compression_methods(); */
	sk_SSL_COMP_free(SSL_COMP_get_compression_methods());
	RAND_cleanup();
}