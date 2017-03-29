#include <type_traits>

#include <rest/api_client.hpp>
#include <rest.hpp>

#include <rest/models/create_dm_channel_args.hpp>
#include <rest/models/create_group_dm_args.hpp>
#include <rest/models/create_message_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace internal
        {
            rest_api_client::rest_api_client(const web::uri& base_uri, std::string acct_token, disccord::token_type type)
                : http_client(base_uri), buckets(), token(acct_token), token_type(type)
            {
                setup_discord_handler();
            }

            rest_api_client::rest_api_client(const web::uri& base_uri, std::string acct_token, disccord::token_type type,
                const web::http::client::http_client_config& client_config)
                    : http_client(base_uri, client_config), buckets(), token(acct_token), token_type(type)
            {
                setup_discord_handler();
            }

            rest_api_client::~rest_api_client()
            {
                for (const auto& entry : buckets)
                {
                    delete entry.second;
                }

                buckets.clear();
            }

            pplx::task<void> rest_api_client::request_empty_internal(route_info& route, const pplx::cancellation_token& token)
            {
                return request_internal(route, token).then([](web::http::http_response response)
                {
                    if (response.status_code() != 204)
                    {
                        throw web::http::http_exception("http response did not return a 204");
                    }
                });
            }

            pplx::task<void> rest_api_client::request_empty_internal(route_info& route, disccord::api::request_info* request, const pplx::cancellation_token& token)
            {
                return request_internal(route, request, token).then([](web::http::http_response response)
                {
                    if (response.status_code() != 204)
                    {
                        throw web::http::http_exception("http response did not return a 204");
                    }
                });
            }

            pplx::task<web::http::http_response> rest_api_client::request_internal(route_info& route, const pplx::cancellation_token& token)
            {
                disccord::api::request_info* info = new disccord::api::request_info();
                return request_internal(route, info, token);
            }

            pplx::task<web::http::http_response> rest_api_client::request_internal(route_info& route, disccord::api::request_info* request, const pplx::cancellation_token& token)
            {
                auto bucket = get_bucket(route);

                request->set_method(route.method);
                request->set_url(web::uri(route.full_url));

                return bucket->enter(http_client, request, token);
            }

            pplx::task<void> rest_api_client::request(route_info& route, const pplx::cancellation_token& token)
            {
                return request_empty_internal(route, token);
            }

            pplx::task<void> rest_api_client::request_multipart(route_info& route, disccord::api::multipart_request args, const pplx::cancellation_token& token)
            {
                disccord::api::request_info* info = new disccord::api::request_info();

                info->set_body(args.encode(), args.get_content_type());
                return request_empty_internal(route, info, token);
            }

            // User API
            pplx::task<disccord::models::user> rest_api_client::get_current_user(const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me");
                return request_json<disccord::models::user>(route, token);
            }

            pplx::task<disccord::models::user> rest_api_client::get_user(uint64_t user_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/{user.id}", std::to_string(user_id));
                return request_json<disccord::models::user>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/guilds");
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/guilds?limit={limit}", std::to_string(limit));
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(std::string query, uint64_t guild_id, const pplx::cancellation_token& token)
            {
                // Here we could be forgiving and default if the user enters a non-existant query param
                // or can be less forgiving and let the bad request go through.
                auto route = get_route("GET", "/users/@me/guilds?{query}={guild}",query,std::to_string(guild_id));
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(std::string query, uint64_t guild_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/guilds?{query}={guild}&limit="+std::to_string(limit), query, std::to_string(guild_id));
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<void> rest_api_client::leave_guild(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/users/@me/guilds/{guild.id}", std::to_string(guild_id));
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::channel>> rest_api_client::get_user_dms(const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/channels");
                return request_multi_json<disccord::models::channel>(route, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::create_dm_channel(uint64_t recipient_id, const pplx::cancellation_token& token)
            {
                disccord::rest::models::create_dm_channel_args args{recipient_id};
                auto route = get_route("POST", "/users/@me/channels");
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::create_group_dm(std::unordered_map<uint64_t, std::string> nicks, std::vector<std::string> access_tokens, const pplx::cancellation_token& token)
            {
                disccord::rest::models::create_group_dm_args args{nicks, access_tokens};
                auto route = get_route("POST", "/users/@me/channels");
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<std::vector<disccord::models::connection>> rest_api_client::get_user_connections(const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/connections");
                return request_multi_json<disccord::models::connection>(route, token);
            }

            // Invite API
            pplx::task<disccord::models::invite> rest_api_client::get_invite(std::string invite_code, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/invites/{invite.code}", invite_code);
                return request_json<disccord::models::invite>(route, token);
            }

            pplx::task<disccord::models::invite> rest_api_client::delete_invite(std::string invite_code, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/invites/{invite.code}", invite_code);
                return request_json<disccord::models::invite>(route, token);
            }

            pplx::task<disccord::models::invite> rest_api_client::accept_invite(std::string invite_code, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/invites/{invite.code}", invite_code);
                return request_json<disccord::models::invite>(route, token);
            }

            // Channel API
            pplx::task<disccord::models::message> rest_api_client::create_message(uint64_t channel_id, std::string content, const pplx::cancellation_token& token)
            {
                disccord::rest::models::create_message_args args{content};
                auto route = get_route("POST", "/channels/{channel.id}/messages",std::to_string(channel_id));
                return request_json<disccord::models::message>(route, args, token);
            }
            
            pplx::task<void> rest_api_client::create_reaction(uint64_t channel_id, uint64_t message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = get_route("PUT", "/channels/{channel.id}/messages/{message.id}/reactions/"+emoji+"/@me", std::to_string(channel_id), std::to_string(message_id));
                return request(route, token);
            }
            
            disccord::api::bucket_info* rest_api_client::get_bucket(route_info& info)
            {
                auto bucket_itr = buckets.find(info.bucket_url);
                if (bucket_itr != buckets.end())
                {
                    return bucket_itr->second;
                }
                else
                {
                    auto bucket = new disccord::api::bucket_info(info.method);
                    buckets.emplace(info.bucket_url, bucket);
                    return bucket;
                }
            }

            void rest_api_client::setup_discord_handler()
            {
                // Set user-agent on a request and add authorization header
                http_client.add_handler([=](auto req, auto pipeline)
                {
                    req.headers().add("User-Agent", DISCORD_USER_AGENT);

                    std::string token_type_s;
                    switch (token_type)
                    {
                        case disccord::token_type::Bearer:
                            token_type_s = "Bearer ";
                            break;
                        case disccord::token_type::Bot:
                            token_type_s = "Bot ";
                            break;
                        case disccord::token_type::User:
                            // user tokens don't have a prefix
                            token_type_s = "";
                            break;
                    }

                    req.headers().add("Authorization", token_type_s + token);
                    return pipeline->propagate(req);
                });
            }
        }
    }
}
