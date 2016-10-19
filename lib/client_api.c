#include <curl/curl.h>
#include <cJSON/cJSON.h>

#include "client.h"
#include "client_internal.h"
#include "message.h"

enum http_method {
	HTTP_GET,
	HTTP_POST
};
enum http_content {
	CONTENT_NONE,
	CONTENT_JSON,
	CONTENT_MULTIPART
};

struct curl_req {
	CURL* handle;
	struct curl_slist* headers;
};


static size_t curl_header_callback(char* buffer, size_t size, size_t nitems, void* userdata) {
	(void)buffer;
	(void)userdata;

	return size * nitems;
}


struct curl_req* setup_request(discord_client_t* client, char* endpoint, size_t len) {
	CURL* handle = curl_easy_init();

	if (!handle)
		return NULL;

	struct curl_req* req = malloc(sizeof(struct curl_req));

	char url[sizeof(DISCORD_API_URL) + len];
	sprintf(url, "%s%s", DISCORD_API_URL, endpoint);

	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_USERAGENT, DISCCORD_USER_AGENT);

	curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, curl_header_callback);
	curl_easy_setopt(handle, CURLOPT_HEADERDATA, req);

	char auth[128];
	sprintf(auth, "Authorization: %s %s", "Bot", client->_token);

	struct curl_slist* ext_headers = curl_slist_append(NULL, auth);

	req->handle = handle;
	req->headers = ext_headers;

	return req;
}

void exec_request(discord_client_t* client, struct curl_req* req, enum http_method method, enum http_content type, char* body) {
	CURL* handle = req->handle;

	switch(method) {
		case HTTP_POST:
		{
			curl_easy_setopt(handle, CURLOPT_POSTFIELDS, body);
			switch (type) {
				case CONTENT_JSON:
					req->headers = curl_slist_append(req->headers, "Content-Type: application/json");
					break;
				default:
					break;
			} 
			break;
		}
		case HTTP_GET:
		{
			curl_easy_setopt(handle, CURLOPT_HTTPGET, 1);
		}
	}

	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, req->headers);

	/* curl_multi_add_handle(client->_curl_handle, handle); */
	curl_easy_perform(handle);

	curl_easy_cleanup(handle);
	curl_slist_free_all(req->headers);
	
	free(req);

	(void)client;
}



void client_send_message(discord_client_t* client, uint64_t channel_id, const char* contents) {
	char endpoint[38]; /* TODO: should we allocate more than this? */
	sprintf(endpoint, "channels/%lu/messages", channel_id);

	struct curl_req* req = setup_request(client, endpoint, 38);

	if (!req)
		return;

	cJSON* root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "content", contents);

	char* data = cJSON_PrintUnformatted(root);
	exec_request(client, req, HTTP_POST, CONTENT_JSON, data);

	cJSON_Delete(root);
}