#include <rest/api_client.hpp>
#include <rest.hpp>

#include <type_traits>

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
            
            // User API
            pplx::task<disccord::models::user> rest_api_client::get_current_user(pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/users/@me");
                return request<disccord::models::user>(route, token);
            }
            
            pplx::task<disccord::models::user> rest_api_client::get_user(uint64_t user_id, pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/users/{user.id}", std::to_string(user_id));
                return request<disccord::models::user>(route, token);
            }
            
            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/users/@me/guilds");
                return request_array<std::vector<disccord::models::user_guild>>(route, token);
            }
            
            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(uint8_t limit, 
                                                                                                            pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/users/@me/guilds?limit={limit}", std::to_string(limit));
                return request_array<std::vector<disccord::models::user_guild>>(route, token);
            }
            
            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(std::string query, uint64_t guild_id,
                                                                                                            pplx::cancellation_token token)
            {
                // Here we could be forgiving and default if the user enters a non-existant query param
                // or can be less forgiving and let the bad request go through.
                auto route = get_route("GET", "/users/@me/guilds?{query}={guild}",query,std::to_string(guild_id));
                return request_array<std::vector<disccord::models::user_guild>>(route, token);
            }
            
            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(std::string query, uint64_t guild_id, uint8_t limit, 
                                                                                                            pplx::cancellation_token token)
            {
                // NOTE: {guild.id} is a reserved major param, so we use {guild} here to not break routing
                auto route = get_route("GET", "/users/@me/guilds?{query}={guild}&limit={limit}", query, std::to_string(guild_id), std::to_string(limit));
                return request_array<std::vector<disccord::models::user_guild>>(route, token);
            }
            
           /*  pplx::task<void> rest_api_client::leave_guild(uint64_t guild_id, pplx::cancellation_token token)
            {
                // TODO: does our request method not break on empty responses? Doubt it.
                auto route = get_route("DELETE", "/users/@me/guilds/{guild.id}", std::to_string(guild_id));
                return request<void>(route, token);
            } */
            
            pplx::task<std::vector<disccord::models::channel>> rest_api_client::get_user_dms(pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/users/@me/channels");
                return request_array<std::vector<disccord::models::channel>>(route, token);
            }
            
            pplx::task<disccord::models::channel> rest_api_client::create_dm(uint64_t recipient_id, 
                                                            pplx::cancellation_token token)
            {
                web::json::value body;
                body["recipient_id"] = web::json::value(recipient_id);
                auto route = get_route("POST", "/users/@me/channels");
                return request<disccord::models::channel>(route, body, token);
            }
            
            pplx::task<disccord::models::channel> rest_api_client::create_group_dm(std::vector<std::string> access_tokens, web::json::value nicks,
                                                                    pplx::cancellation_token token)
            {
                web::json::value body;
                std::vector<web::json::value> token_array; // This could probably be generalized to use for other endpoints
                for (auto i : access_tokens)
                   token_array.push_back(web::json::value(i));
                body["access_tokens"] = web::json::value::array(token_array);
                body["nicks"] = nicks;
                auto route = get_route("POST", "/users/@me/channels");
                return request<disccord::models::channel>(route, body, token);
            }
            
            pplx::task<std::vector<disccord::models::connection>> rest_api_client::get_user_connections(pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/users/@me/connections");
                return request_array<std::vector<disccord::models::connection>>(route, token);
            }
            
            
            // Invite API
            pplx::task<disccord::models::invite> rest_api_client::get_invite(std::string invite_code, pplx::cancellation_token token)
            {
                auto route = get_route("GET", "/invites/{invite.code}", invite_code);
                return request<disccord::models::invite>(route, token);
            }
            
            pplx::task<disccord::models::invite> rest_api_client::delete_invite(std::string invite_code, pplx::cancellation_token token)
            {
                auto route = get_route("DELETE", "/invites/{invite.code}", invite_code);
                return request<disccord::models::invite>(route, token);
            }
            
            pplx::task<disccord::models::invite> rest_api_client::accept_invite(std::string invite_code, pplx::cancellation_token token)
            {
                auto route = get_route("POST", "/invites/{invite.code}", invite_code);
                return request<disccord::models::invite>(route, token);
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
                http_client.add_handler([=](auto req, auto pipeline){
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