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

#include <disccord/models/rest/guild_prune_args.hpp>
#include <disccord/models/rest/edit_current_user_nick_args.hpp>
#include <disccord/models/rest/add_guild_member_args.hpp>
#include <disccord/models/rest/create_channel_invite_args.hpp>
#include <disccord/models/rest/create_guild_channel_args.hpp>
#include <disccord/models/rest/create_message_args.hpp>
#include <disccord/models/rest/edit_message_args.hpp>
#include <disccord/models/rest/edit_guild_role_args.hpp>
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
                    rest_api_client(const web::uri& base_uri, const std::string& token, disccord::token_type type);
                    rest_api_client(const web::uri& base_uri, const std::string& token, disccord::token_type type, const web::http::client::http_client_config& client_config);
                    virtual ~rest_api_client();

                    // Websockets
                    pplx::task<disccord::models::gateway_info> get_gateway(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::gateway_info> get_gateway_bot(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // User API
                    pplx::task<disccord::models::user> get_current_user(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::user> get_user(const disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::user> edit_current_user(const disccord::models::rest::edit_current_user_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(const uint8_t limit = 100, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds_before(const disccord::snowflake guild_id, const uint8_t limit = 100, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds_after(const disccord::snowflake guild_id, const uint8_t limit = 100, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> leave_guild(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::channel>> get_user_dms(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_dm_channel(const disccord::snowflake recipient_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_group_dm(const std::unordered_map<disccord::snowflake, std::string> nicks, const std::vector<std::string> access_tokens, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::connection>> get_user_connections(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Invite API
                    pplx::task<disccord::models::invite> get_invite(const std::string& invite_code, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> delete_invite(const std::string& invite_code, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> accept_invite(const std::string& invite_code, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Channel API
                    pplx::task<disccord::models::channel> get_channel(const disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> edit_channel(const disccord::snowflake channel_id, const disccord::models::rest::edit_channel_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> delete_channel(const disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_channel_messages(const disccord::snowflake channel_id, const uint8_t limit = 50, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_channel_messages_before(const disccord::snowflake channel_id, const disccord::snowflake message_id, const uint8_t limit = 50, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_channel_messages_after(const disccord::snowflake channel_id, const disccord::snowflake message_id, const uint8_t limit = 50, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> get_message(const disccord::snowflake channel_id, const disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> create_message(const disccord::snowflake channel_id, const disccord::models::rest::create_message_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> create_message(const disccord::snowflake channel_id, const disccord::api::multipart_request args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> create_reaction(const disccord::snowflake channel_id, const disccord::snowflake message_id, const std::string& emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_own_reaction(const disccord::snowflake channel_id, const disccord::snowflake message_id, const std::string& emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_user_reaction(const disccord::snowflake channel_id, const disccord::snowflake message_id, const disccord::snowflake user_id, const std::string& emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user>> get_reactions(const disccord::snowflake channel_id, const disccord::snowflake message_id, const std::string& emoji, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_all_reactions(const disccord::snowflake channel_id, const disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::message> edit_message(const disccord::snowflake channel_id, const disccord::snowflake message_id, const disccord::models::rest::edit_message_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_message(const disccord::snowflake channel_id, const disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> bulk_delete_messages(const disccord::snowflake channel_id, const std::vector<disccord::snowflake> message_ids, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_channel_permissions(const disccord::snowflake channel_id, const disccord::snowflake overwrite_id, const disccord::permissions allow, const disccord::permissions deny, const std::string& type, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::invite>> get_channel_invites(const disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> create_channel_invite(const disccord::snowflake channel_id, const disccord::models::rest::create_channel_invite_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_channel_permissions(const disccord::snowflake channel_id, const disccord::snowflake overwrite_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> trigger_typing(const disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::message>> get_pinned_messages(const disccord::snowflake channel_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> pin_message(const disccord::snowflake channel_id, const disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> unpin_message(const disccord::snowflake channel_id, const disccord::snowflake message_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> add_dm_recipient(const disccord::snowflake channel_id, const disccord::snowflake user_id, const std::string& access_token, const std::string& nick, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_dm_recipient(const disccord::snowflake channel_id, const disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    // Guild API
                    pplx::task<disccord::models::guild> get_guild(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild> edit_guild(const disccord::snowflake guild_id, const disccord::models::rest::edit_guild_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild> delete_guild(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::channel>> get_guild_channels(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_guild_channel(const disccord::snowflake guild_id, const disccord::models::rest::create_guild_channel_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_channel_positions(const disccord::snowflake guild_id, const disccord::models::rest::edit_positions_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_member> get_guild_member(const disccord::snowflake guild_id, const disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::guild_member>> list_guild_members(const disccord::snowflake guild_id, const uint16_t limit = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::guild_member>> list_guild_members_before(const disccord::snowflake guild_id, const disccord::snowflake user_id, const uint16_t limit = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::guild_member>> list_guild_members_after(const disccord::snowflake guild_id, const disccord::snowflake user_id, const uint16_t limit = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_member> add_guild_member(const disccord::snowflake guild_id, const disccord::snowflake user_id, const disccord::models::rest::add_guild_member_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_member(const disccord::snowflake guild_id, const disccord::snowflake user_id, const disccord::models::rest::edit_guild_member_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::rest::edit_current_user_nick_args> edit_current_user_nick(const disccord::snowflake guild_id, const std::string& nick, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> add_guild_member_role(const disccord::snowflake guild_id, const disccord::snowflake user_id, const disccord::snowflake role_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_guild_member_role(const disccord::snowflake guild_id, const disccord::snowflake user_id, const disccord::snowflake role_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_guild_member(const disccord::snowflake guild_id, const disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::user>> get_guild_bans(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> create_guild_ban(const disccord::snowflake guild_id, const disccord::snowflake user_id, const uint8_t delete_message_days, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> remove_guild_ban(const disccord::snowflake guild_id, const disccord::snowflake user_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::role>> get_guild_roles(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::role> create_guild_role(const disccord::snowflake guild_id, const disccord::models::rest::edit_guild_role_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_role_positions(const disccord::snowflake guild_id, const disccord::models::rest::edit_positions_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::role> edit_guild_role(const disccord::snowflake guild_id, const disccord::models::rest::edit_guild_role_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_guild_role(const disccord::snowflake guild_id, const disccord::snowflake role_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::rest::guild_prune_args> get_guild_prune_count(const disccord::snowflake guild_id, const uint32_t days = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::rest::guild_prune_args> begin_guild_prune(const disccord::snowflake guild_id, const uint32_t days = 1, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::voice_region>> get_guild_voice_regions(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::invite>> get_guild_invites(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::integration>> get_guild_integrations(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> create_guild_integration(const disccord::snowflake guild_id, const disccord::snowflake integration_id, const std::string& type, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> edit_guild_integration(const disccord::snowflake guild_id, const disccord::snowflake integration_id, const uint32_t expire_behavior, const uint32_t expire_grace_period, const bool enable_emoticons, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> delete_guild_integration(const disccord::snowflake guild_id, const disccord::snowflake integration_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> sync_guild_integration(const disccord::snowflake guild_id, const disccord::snowflake integration_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_embed> get_guild_embed(const disccord::snowflake guild_id, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::guild_embed> edit_guild_embed(const disccord::snowflake guild_id, const disccord::models::rest::edit_guild_embed_args args, const pplx::cancellation_token& token = pplx::cancellation_token::none());

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
