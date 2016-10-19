#include "websocket.h"
#include "websocket_internal.h"

int discord_protocol(struct lws* wsi, enum lws_callback_reasons reason,
		void* user, void* in, size_t len) {

	client_websocket_t* client = (client_websocket_t*)user;

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