#ifndef _rest_api_client_hpp_
#define _rest_api_client_hpp_

#include <unordered_map>
#include <vector>
#include <utility>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <disccord/api/bucket_info.hpp>
#include <disccord/api/multipart_request.hpp>
#include <disccord/rest/route.hpp>
#include <disccord/types.hpp>

#include <disccord/models/gateway_info.hpp>
#include <disccord/models/channel.hpp>
#include <disccord/models/connection.hpp>
#include <disccord/models/guild.hpp>
#include <disccord/models/guild_embed.hpp>
#include <disccord/models/guild_member.hpp>
#include <disccord/models/integration.hpp>
#include <disccord/models/invite.hpp>
#include <disccord/models/message.hpp>
#include <disccord/models/role.hpp>
#include <disccord/models/user.hpp>
#include <disccord/models/user_guild.hpp>
#include <disccord/models/voice_region.hpp>

#include <disccord/models/rest/guild_prune.hpp>
#include <disccord/models/rest/nickname.hpp>
#include <disccord/models/rest/add_guild_member_args.hpp>
#include <disccord/models/rest/create_channel_invite_args.hpp>
#include <disccord/models/rest/create_guild_channel_args.hpp>
#include <disccord/models/rest/create_message_args.hpp>
#include <disccord/models/rest/edit_message_args.hpp>
#include <disccord/models/rest/guild_role_args.hpp>
#include <disccord/models/rest/edit_channel_args.hpp>
#include <disccord/models/rest/edit_guild_args.hpp>
#include <disccord/models/rest/edit_guild_embed_args.hpp>
#include <disccord/models/rest/edit_guild_member_args.hpp>
#include <disccord/models/rest/edit_positions_args.hpp>
#include <disccord/models/rest/edit_current_user_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace internal
        {
            class rest_api_client
            {
                public:
                    rest_api_client(const web::uri& base_uri, std::string token, disccord::token_type type);
                    rest_api_client(const web::uri& base_uri, std::string token, disccord::token_type type, const web::http::client::http_client_config& client_config);
                    virtual ~rest_api_client();

                    // Websockets
                    pplx::task<disccord::models::gateway_info> get_gateway(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::gateway_info> get_gateway_bot(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // User API
                    pplx::task<disccord::models::user> get_current_user(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::user> get_user(disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::user> edit_current_user(disccord::rest::models::edit_current_user_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(uint8_t limit = 100, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds_before(disccord::snowflake guild_id, uint8_t limit = 100, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds_after(disccord::snowflake guild_id, uint8_t limit = 100, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> leave_guild(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::channel>> get_user_dms(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_dm_channel(disccord::snowflake recipient_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_group_dm(std::unordered_map<disccord::snowflake, std::string> nicks, std::vector<std::string> access_tokens, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::connection>> get_user_connections(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Invite API
                    pplx::task<disccord::models::invite> get_invite(std::string invite_code, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> delete_invite(std::string invite_code, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> accept_invite(std::string invite_code, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Channel API
                    pplx::task<disccord::models::channel> get_channel(disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> edit_channel(disccord::snowflake channel_id, disccord::models::rest::edit_channel_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> delete_channel(disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_channel_messages(disccord::snowflake channel_id, uint8_t limit = 50, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_channel_messages_before(disccord::snowflake channel_id, disccord::snowflake message_id, uint8_t limit = 50, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_channel_messages_after(disccord::snowflake channel_id, disccord::snowflake message_id, uint8_t limit = 50, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> get_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> create_message(disccord::snowflake channel_id, disccord::models::rest::create_message_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> create_message(disccord::snowflake channel_id, disccord::api::multipart_request args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> create_reaction(disccord::snowflake channel_id, disccord::snowflake message_id, std::string emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_own_reaction(disccord::snowflake channel_id, disccord::snowflake message_id, std::string emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_user_reaction(disccord::snowflake channel_id, disccord::snowflake message_id, disccord::snowflake user_id, std::string emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user>> get_reactions(disccord::snowflake channel_id, disccord::snowflake message_id, std::string emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_all_reactions(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> edit_message(disccord::snowflake channel_id, disccord::snowflake message_id, disccord::models::rest::edit_message_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> bulk_delete_messages(disccord::snowflake channel_id, std::vector<disccord::snowflake> message_ids, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_channel_permissions(disccord::snowflake channel_id, disccord::snowflake overwrite_id, disccord::permissions allow, disccord::permissions deny, std::string type, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::invite>> get_channel_invites(disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> create_channel_invite(disccord::snowflake channel_id, disccord::models::rest::create_channel_invite_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_channel_permissions(disccord::snowflake channel_id, disccord::snowflake overwrite_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> trigger_typing(disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_pinned_messages(disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> pin_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> unpin_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> add_dm_recipient(disccord::snowflake channel_id, disccord::snowflake user_id, std::string access_token, std::string nick, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_dm_recipient(disccord::snowflake channel_id, disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Guild API
                    pplx::task<disccord::models::guild> get_guild(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild> edit_guild(disccord::snowflake guild_id, disccord::models::rest::edit_guild_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild> delete_guild(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::channel>> get_guild_channels(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_guild_channel(disccord::snowflake guild_id, disccord::models::rest::create_guild_channel_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_channel_positions(disccord::snowflake guild_id, disccord::models::rest::edit_positions_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_member> get_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::guild_member>> list_guild_members(disccord::snowflake guild_id, uint16_t limit = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::guild_member>> list_guild_members_before(disccord::snowflake guild_id, disccord::snowflake user_id, uint16_t limit, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::guild_member>> list_guild_members_after(disccord::snowflake guild_id, disccord::snowflake user_id, uint16_t limit, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_member> add_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::models::rest::add_guild_member_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::models::rest::edit_guild_member_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::rest::models::nickname> edit_current_nick(uint64_t guild_id, std::string nick, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> add_guild_member_role(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::snowflake role_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_guild_member_role(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::snowflake role_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user>> get_guild_bans(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> create_guild_ban(disccord::snowflake guild_id, disccord::snowflake user_id, uint8_t delete_message_days, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_guild_ban(disccord::snowflake guild_id, disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::role>> get_guild_roles(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::role> create_guild_role(disccord::snowflake guild_id, disccord::models::rest::edit_guild_role_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_role_positions(disccord::snowflake guild_id, disccord::models::rest::edit_positions_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::role> edit_guild_role(disccord::snowflake guild_id, disccord::models::rest::edit_guild_role_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_guild_role(disccord::snowflake guild_id, disccord::snowflake role_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::rest::models::guild_prune> get_guild_prune_count(uint64_t guild_id, uint32_t days = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::rest::models::guild_prune> begin_guild_prune(uint64_t guild_id, uint32_t days = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::voice_region>> get_guild_voice_regions(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::invite>> get_guild_invites(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::integration>> get_guild_integrations(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> create_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, std::string type, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, uint32_t expire_behavior, uint32_t expire_grace_period, bool enable_emoticons, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> sync_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_embed> get_guild_embed(disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_embed> edit_guild_embed(disccord::snowflake guild_id, disccord::models::rest::edit_guild_embed_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Voice API
                    pplx::task<std::vector<disccord::models::voice_region>> list_voice_regions(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                private:
                    pplx::task<void> request_empty_internal(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none());
                    pplx::task<void> request_empty_internal(route_info& route, disccord::api::request_info* request, const pplx::cancellation_token& token = pplx::cancellation_token::none());
                    pplx::task<web::http::http_response> request_internal(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none());
                    pplx::task<web::http::http_response> request_internal(route_info& route, disccord::api::request_info* request, const pplx::cancellation_token& token = pplx::cancellation_token::none());
                    disccord::api::bucket_info* get_bucket(route_info& route);

                    web::http::client::http_client http_client;
                    std::unordered_map<std::string, disccord::api::bucket_info*> buckets;
                    std::string token;
                    disccord::token_type token_type;
                    void setup_discord_handler();

                    pplx::task<void> request(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    template <typename TResponse>
                    pplx::task<TResponse> request_json(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        return request_internal(route, token).then([](web::http::http_response response)
                        {
                            return response.extract_json();
                        }).then([](web::json::value response)
                        {
                            TResponse result;
                            result.decode(response);
                            return result;
                        });
                    }

                    template <typename TResponse, typename TModel>
                    pplx::task<TResponse> request_json(route_info& route, TModel body, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        info->set_body(body.encode());
                        return request_internal(route, info, token).then([](web::http::http_response response)
                        {
                            return response.extract_json();
                        }).then([](web::json::value response)
                        {
                            TResponse result;
                            result.decode(response);
                            return result;
                        });
                    }

                    template <typename TModel>
                    pplx::task<void> request_json(route_info& route, TModel body, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        info->set_body(body.encode());
                        return request_internal(route, info, token).then([](web::http::http_response response)
                        {});
                    }

                    template <typename TModel>
                    pplx::task<void> request_multi_json(route_info& route, std::vector<TModel> body, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        std::vector<web::json::value> body_arr(body.size());
                        std::transform(body.begin(), body.end(), body_arr.size(), [](TModel value)
                        {
                            return value.encode();
                        });

                        web::json::value _body = web::json::value::array(body_arr);

                        info->set_body(_body);
                        return request_internal(route, info, token).then([](web::http::http_response response)
                        {
                            return response.extract_json();
                        });
                    }

                    template <typename TResponse>
                    pplx::task<std::vector<TResponse>> request_multi_json(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        return request_internal(route, token).then([](web::http::http_response response)
                        {
                            return response.extract_json();
                        }).then([](web::json::value response)
                        {
                            if (response.is_array())
                            {
                                auto response_arr = response.as_array();
                                std::vector<TResponse> responses(response_arr.size());
                                std::transform(response_arr.begin(), response_arr.end(), responses.begin(), [](web::json::value item)
                                {
                                    TResponse result;
                                    result.decode(item);
                                    return result;
                                });
                                return responses;
                            }
                            else
                            {
                                std::vector<TResponse> responses;
                                TResponse result;
                                result.decode(response);
                                responses.push_back(result);
                                return responses;
                            }
                        });
                    }

                    template <typename TResponse, typename TModel>
                    pplx::task<std::vector<TResponse>> request_multi_json(route_info& route, std::vector<TModel> body, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        std::vector<web::json::value> body_arr(body.size());
                        std::transform(body.begin(), body.end(), body_arr.size(), [](TModel value)
                        {
                            return value.encode();
                        });

                        web::json::value _body = web::json::value::array(body_arr);

                        info->set_body(_body);
                        return request_internal(route, info, token).then([](web::http::http_response response)
                        {
                            return response.extract_json();
                        }).then([](web::json::value response)
                        {
                            if (response.is_array())
                            {
                                auto response_arr = response.as_array();
                                std::vector<TResponse> responses(response_arr.size());
                                std::transform(response_arr.begin(), response_arr.end(), responses.begin(), [](web::json::value item)
                                {
                                    TResponse result;
                                    result.decode(item);
                                    return result;
                                });
                                return responses;
                            }
                            else
                            {
                                std::vector<TResponse> responses;
                                TResponse result;
                                result.decode(response);
                                responses.push_back(result);
                                return responses;
                            }
                        });
                    }

                    pplx::task<void> request_multipart(route_info& route, disccord::api::multipart_request args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    template <typename TResponse>
                    pplx::task<TResponse> request_multipart(route_info& route, disccord::api::multipart_request args, const pplx::cancellation_token& token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        info->set_body(args.encode(), args.get_content_type());
                        return request_internal(route, info, token).then([](web::http::http_response response)
                        {
                            return response.extract_json();
                        }).then([](web::json::value response)
                        {
                            TResponse result;
                            result.decode(response);
                            return result;
                        });
                    }
            };
        }
    }
}

#endif /* _rest_client_hpp_ */
