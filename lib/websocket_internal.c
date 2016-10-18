#include "websocket.h"
#include "websocket_internal.h"

/* This is here purely for debugging reasons. */
static char* callback_reasons[] = {
	"LWS_CALLBACK_ESTABLISHED",
	"LWS_CALLBACK_CLIENT_CONNECTION_ERROR",
	"LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH",
	"LWS_CALLBACK_CLIENT_ESTABLISHED",
	"LWS_CALLBACK_CLOSED",
	"LWS_CALLBACK_CLOSED_HTTP",
	"LWS_CALLBACK_RECEIVE",
	"LWS_CALLBACK_RECEIVE_PONG",
	"LWS_CALLBACK_CLIENT_RECEIVE",
	"LWS_CALLBACK_CLIENT_RECEIVE_PONG",
	"LWS_CALLBACK_CLIENT_WRITEABLE",
	"LWS_CALLBACK_SERVER_WRITEABLE",
	"LWS_CALLBACK_HTTP",
	"LWS_CALLBACK_HTTP_BODY",
	"LWS_CALLBACK_HTTP_BODY_COMPLETION",
	"LWS_CALLBACK_FILE_COMPLETION",
	"LWS_CALLBACK_HTTP_WRITEABLE",
	"LWS_CALLBACK_FILTER_NETWORK_CONNECTION",
	"LWS_CALLBACK_FILTER_HTTP_CONNECTION",
	"LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED",
	"LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION",
	"LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS",
	"LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS",
	"LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION",
	"LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER",
	"LWS_CALLBACK_CONFIRM_EXTENSION_OKAY",
	"LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED",
	"LWS_CALLBACK_PROTOCOL_INIT",
	"LWS_CALLBACK_PROTOCOL_DESTROY",
	"LWS_CALLBACK_WSI_CREATE",
	"LWS_CALLBACK_WSI_DESTROY",
	"LWS_CALLBACK_GET_THREAD_ID",
	"LWS_CALLBACK_ADD_POLL_FD",
	"LWS_CALLBACK_DEL_POLL_FD",
	"LWS_CALLBACK_CHANGE_MODE_POLL_FD",
	"LWS_CALLBACK_LOCK_POLL",
	"LWS_CALLBACK_UNLOCK_POLL",
	"LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY",
	"LWS_CALLBACK_WS_PEER_INITIATED_CLOSE",
	"LWS_CALLBACK_WS_EXT_DEFAULTS",
	"LWS_CALLBACK_CGI",
	"LWS_CALLBACK_CGI_TERMINATED",
	"LWS_CALLBACK_CGI_STDIN_DATA",
	"LWS_CALLBACK_CGI_STDIN_COMPLETED",
	"LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP",
	"LWS_CALLBACK_CLOSED_CLIENT_HTTP",
	"LWS_CALLBACK_RECEIVE_CLIENT_HTTP",
	"LWS_CALLBACK_COMPLETED_CLIENT_HTTP",
	"LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ",
	"LWS_CALLBACK_HTTP_BIND_PROTOCOL",
	"LWS_CALLBACK_HTTP_DROP_PROTOCOL",
	"LWS_CALLBACK_CHECK_ACCESS_RIGHTS",
	"LWS_CALLBACK_PROCESS_HTML",
	"LWS_CALLBACK_ADD_HEADERS",
	"LWS_CALLBACK_SESSION_INFO",
	"LWS_CALLBACK_GS_EVENT",
	"LWS_CALLBACK_HTTP_PMO",
	"LWS_CALLBACK_CLIENT_HTTP_WRITEABLE"
};

int discord_protocol(struct lws* wsi, enum lws_callback_reasons reason,
		void* user, void* in, size_t len) {

	client_websocket_t* client = (client_websocket_t*)user;

	printf("Callback %i (%s)\n", reason, callback_reasons[reason]);

	/* TODO: figure out what's causing this to degfault */
	/*
	if (client->_disconnect) {
		lws_close_reason(wsi, LWS_CLOSE_STATUS_NORMAL, "", 0);
		client->_connected = 0;
		client->_remain_connected = 0;
		
		return 1;
	}
	*/

	switch (reason) {
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		{
			if (client->_callbacks->on_connection_error) {
				if (in && len)
					client->_callbacks->on_connection_error(client, (char*)in, len);
				else
					client->_callbacks->on_connection_error(client, "Unknown", 7);
			}

			client->_connected = 0;
			break;
		}
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
		{
			break;
		}
		case LWS_CALLBACK_CLOSED:
		{
			break;
		}
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
		{
			uint16_t close_reason = ntohs(*(uint16_t*)in);

			char buffer[50];
			size_t close_len = sprintf(buffer, "Server sent close %hu", close_reason);

			client->_callbacks->on_connection_error(client, buffer, close_len);

			break;
		}
		case LWS_CALLBACK_CLIENT_RECEIVE:
		{
			size_t old_length = client->_current_packet_length;
			size_t new_length = old_length + len;
			void* new_data = realloc(client->_current_packet, new_length);
			if (new_data) {
				client->_current_packet = (char*)new_data;
				client->_current_packet_length = new_length;
			} else {
				return 1;
			}

			memcpy(client->_current_packet + old_length, in, len);
			
			if (lws_is_final_fragment(wsi)) {
				char* data = client->_current_packet;
				size_t data_len = client->_current_packet_length;
				data[data_len] = '\0';

				int success = 0;

				if (client->_callbacks->on_receive)
					success = client->_callbacks->on_receive(client, data, data_len);

				free(client->_current_packet);
				client->_current_packet = NULL;
				client->_current_packet_length = 0;

				return success;
			}

			break;
		}
		case LWS_CALLBACK_GET_THREAD_ID:
		{
			return pthread_self();
		}
		case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
		{
			return 1;
		}
		default:
		{
			break;
		}
	}

	return 0;
}