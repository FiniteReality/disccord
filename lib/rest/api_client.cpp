#include <type_traits>

#include <disccord/rest/api_client.hpp>
#include <disccord/rest.hpp>

#include <disccord/util/url_encode.hpp>

#include <disccord/models/rest/add_guild_member_args.hpp>
#include <disccord/models/rest/create_dm_channel_args.hpp>
#include <disccord/models/rest/create_group_dm_args.hpp>
#include <disccord/models/rest/create_guild_ban_args.hpp>
#include <disccord/models/rest/create_guild_channel_args.hpp>
#include <disccord/models/rest/create_guild_integration_args.hpp>
#include <disccord/models/rest/create_message_args.hpp>
#include <disccord/models/rest/edit_guild_role_args.hpp>
#include <disccord/models/rest/edit_guild_args.hpp>
#include <disccord/models/rest/edit_guild_embed_args.hpp>
#include <disccord/models/rest/edit_guild_integration_args.hpp>
#include <disccord/models/rest/edit_guild_member_args.hpp>
#include <disccord/models/rest/edit_positions_args.hpp>
#include <disccord/models/rest/bulk_delete_message_args.hpp>
#include <disccord/models/rest/edit_channel_permissions_args.hpp>
#include <disccord/models/rest/add_dm_recipient_args.hpp>

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
                        std::string err = "HTTP Error: ["+std::to_string(response.status_code())+"] "+response.reason_phrase();
                        throw web::http::http_exception(err);
                    }
                });
            }

            pplx::task<void> rest_api_client::request_empty_internal(route_info& route, disccord::api::request_info* request, const pplx::cancellation_token& token)
            {
                return request_internal(route, request, token).then([](web::http::http_response response)
                {
                    if (response.status_code() != 204)
                    {
                        std::string err = "HTTP Error: ["+std::to_string(response.status_code())+"] "+response.reason_phrase();
                        throw web::http::http_exception(err);
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

                return bucket->enter(http_client, request, token).then([](web::http::http_response response)
                {
                    auto status_code = response.status_code();
                    if (status_code != 204 && status_code != 200)
                    {
                        std::string err = "HTTP Error: ["+std::to_string(response.status_code())+"] "+response.reason_phrase();
                        throw web::http::http_exception(err);
                    }

                    return response;
                });
            }

            pplx::task<void> rest_api_client::request(route_info& route, const pplx::cancellation_token& token)
            {
                if (route.method != "GET") //can be refactored, but need content-length for these requests to succeed.
                {
                    disccord::api::request_info* info = new disccord::api::request_info();
                    info->set_body(web::json::value(""));
                    return request_empty_internal(route, info, token);
                }
                else
                    return request_empty_internal(route, token);
            }

            pplx::task<void> rest_api_client::request_multipart(route_info& route, disccord::api::multipart_request args, const pplx::cancellation_token& token)
            {
                disccord::api::request_info* info = new disccord::api::request_info();

                info->set_body(args.encode(), args.get_content_type());
                return request_empty_internal(route, info, token);
            }

            // Websocket

            pplx::task<disccord::models::gateway_info> rest_api_client::get_gateway(const pplx::cancellation_token& token)
            {
                auto route = build_route<0>("GET", "/gateway", {});
                return request_json<disccord::models::gateway_info>(route, token);
            }

            pplx::task<disccord::models::gateway_info> rest_api_client::get_gateway_bot(const pplx::cancellation_token& token)
            {
                if (token_type != disccord::token_type::BOT)
                    throw new std::runtime_error("token_type must be disccord::token_type::BOT"); // TODO: custom exception type?
                
                auto route = build_route<0>("GET", "/gateway/bot", {});
                return request_json<disccord::models::gateway_info>(route, token);
            }

            // User API
            pplx::task<disccord::models::user> rest_api_client::get_current_user(const pplx::cancellation_token& token)
            {
                auto route = build_route<0>("GET", "/users/@me", {});
                return request_json<disccord::models::user>(route, token);
            }

            pplx::task<disccord::models::user> rest_api_client::get_user(disccord::snowflake user_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/users/{user.id}", {std::to_string(user_id)});
                return request_json<disccord::models::user>(route, token);
            }

            //TODO: edit_current_user

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/users/@me/guilds?limit={limit}", {std::to_string(limit)});
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds_before(disccord::snowflake guild_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/users/@me/guilds?before={guild}&limit={limit}", {std::to_string(guild_id), std::to_string(limit)});
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds_after(disccord::snowflake guild_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/users/@me/guilds?after={guild}&limit={limit}", {std::to_string(guild_id), std::to_string(limit)});
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<void> rest_api_client::leave_guild(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("DELETE", "/users/@me/guilds/{guild.id}", {std::to_string(guild_id)});
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::channel>> rest_api_client::get_user_dms(const pplx::cancellation_token& token)
            {
                auto route = build_route<0>("GET", "/users/@me/channels", {});
                return request_multi_json<disccord::models::channel>(route, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::create_dm_channel(disccord::snowflake recipient_id, const pplx::cancellation_token& token)
            {
                disccord::models::rest::create_dm_channel_args args{recipient_id};
                auto route = build_route<0>("POST", "/users/@me/channels", {});
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::create_group_dm(std::unordered_map<disccord::snowflake, std::string> nicks, std::vector<std::string> access_tokens, const pplx::cancellation_token& token)
            {
                throw new std::runtime_error("not implemented");
                //disccord::models::rest::create_group_dm_args args{nicks, access_tokens};
                //auto route = build_route<0>("POST", "/users/@me/channels", {});
                //return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<std::vector<disccord::models::connection>> rest_api_client::get_user_connections(const pplx::cancellation_token& token)
            {
                auto route = build_route<0>("GET", "/users/@me/connections", {});
                return request_multi_json<disccord::models::connection>(route, token);
            }

            // Invite API
            pplx::task<disccord::models::invite> rest_api_client::get_invite(std::string invite_code, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/invites/{invite.code}", {invite_code});
                return request_json<disccord::models::invite>(route, token);
            }

            pplx::task<disccord::models::invite> rest_api_client::delete_invite(std::string invite_code, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("DELETE", "/invites/{invite.code}", {invite_code});
                return request_json<disccord::models::invite>(route, token);
            }

            pplx::task<disccord::models::invite> rest_api_client::accept_invite(std::string invite_code, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/invites/{invite.code}", {invite_code});
                return request_json<disccord::models::invite>(route, token);
            }

            // Channel API
            pplx::task<disccord::models::channel> rest_api_client::get_channel(disccord::snowflake channel_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/channels/{channel.id}", {std::to_string(channel_id)});
                return request_json<disccord::models::channel>(route, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::edit_channel(disccord::snowflake channel_id, disccord::models::rest::edit_channel_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("PATCH", "/channels/{channel.id}", {std::to_string(channel_id)});
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::delete_channel(disccord::snowflake channel_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("DELETE", "/channels/{channel.id}", {std::to_string(channel_id)});
                return request_json<disccord::models::channel>(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_channel_messages(disccord::snowflake channel_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/channels/{channel.id}/messages?limit={limit}", {std::to_string(channel_id), std::to_string(limit)});
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_channel_messages_before(disccord::snowflake channel_id, disccord::snowflake message_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/channels/{channel.id}/messages?before={message}&limit=limit", {std::to_string(channel_id), std::to_string(message_id)});
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_channel_messages_after(disccord::snowflake channel_id, disccord::snowflake message_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("GET", "/channels/{channel.id}/messages?after={message}&limit={limit}", {std::to_string(channel_id), std::to_string(message_id), std::to_string(limit)});
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<disccord::models::message> rest_api_client::get_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/channels/{channel.id}/messages/{message.id}", {std::to_string(channel_id), std::to_string(message_id)});
                return request_json<disccord::models::message>(route, token);
            }

            pplx::task<disccord::models::message> rest_api_client::create_message(disccord::snowflake channel_id, disccord::models::rest::create_message_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/channels/{channel.id}/messages", {std::to_string(channel_id)});
                return request_json<disccord::models::message>(route, args, token);
            }

            pplx::task<disccord::models::message> rest_api_client::create_message(disccord::snowflake channel_id, disccord::api::multipart_request args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/channels/{channel.id}/messages", {std::to_string(channel_id)});
                return request_multipart<disccord::models::message>(route, args, token);
            }

            pplx::task<void> rest_api_client::create_reaction(disccord::snowflake channel_id, disccord::snowflake message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("PUT", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me", {std::to_string(channel_id), std::to_string(message_id), util::url_encode(emoji)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::delete_own_reaction(disccord::snowflake channel_id, disccord::snowflake message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("DELETE", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me", {std::to_string(channel_id), util::url_encode(emoji), std::to_string(message_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::delete_user_reaction(disccord::snowflake channel_id, disccord::snowflake message_id, disccord::snowflake user_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = build_route<4>("DELETE", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}", {std::to_string(channel_id), std::to_string(message_id), util::url_encode(emoji), std::to_string(user_id)});
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::user>> rest_api_client::get_reactions(disccord::snowflake channel_id, disccord::snowflake message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("GET", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}", {std::to_string(channel_id), std::to_string(message_id), util::url_encode(emoji)});
                return request_multi_json<disccord::models::user>(route, token);
            }

            pplx::task<void> rest_api_client::delete_all_reactions(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/channels/{channel.id}/messages/{message.id}/reactions", {std::to_string(channel_id), std::to_string(message_id)});
                return request(route, token);
            }

            pplx::task<disccord::models::message> rest_api_client::edit_message(disccord::snowflake channel_id, disccord::snowflake message_id, disccord::models::rest::edit_message_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("PATCH", "/channels/{channel.id}/messages/{message.id}", {std::to_string(channel_id), std::to_string(message_id)});
                return request_json<disccord::models::message>(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/channels/{channel.id}/messages/{message.id}", {std::to_string(channel_id), std::to_string(message_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::bulk_delete_messages(disccord::snowflake channel_id, std::vector<disccord::snowflake> message_ids, const pplx::cancellation_token& token)
            {
                throw new std::runtime_error("not implemented");
                //disccord::models::rest::bulk_delete_message_args args{message_ids};
                //auto route = build_route<1>("DELETE", "/channels/{channel.id}/messages/bulk-delete", {std::to_string(channel_id)});
                //return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::edit_channel_permissions(disccord::snowflake channel_id, disccord::snowflake overwrite_id, disccord::permissions allow, disccord::permissions deny, std::string type, const pplx::cancellation_token& token)
            {
                disccord::models::rest::edit_channel_permissions_args args{type, allow, deny};
                auto route = build_route<2>("PUT", "/channels/{channel.id}/permissions/{overwrite.id}", {std::to_string(channel_id), std::to_string(overwrite_id)});
                return request_json(route, args, token);
            }

            pplx::task<std::vector<disccord::models::invite>> rest_api_client::get_channel_invites(disccord::snowflake channel_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/channels/{channel.id}/invites", {std::to_string(channel_id)});
                return request_multi_json<disccord::models::invite>(route, token);
            }

            pplx::task<disccord::models::invite> rest_api_client::create_channel_invite(disccord::snowflake channel_id, disccord::models::rest::create_channel_invite_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/channels/{channel.id}/invites", {std::to_string(channel_id)});
                return request_json<disccord::models::invite>(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_channel_permissions(disccord::snowflake channel_id, disccord::snowflake overwrite_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/channels/{channel.id}/permissions/{overwrite.id}", {std::to_string(channel_id), std::to_string(overwrite_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::trigger_typing(disccord::snowflake channel_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/channels/{channel.id}/typing", {std::to_string(channel_id)});
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_pinned_messages(disccord::snowflake channel_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/channels/{channel.id}/pins", {std::to_string(channel_id)});
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<void> rest_api_client::pin_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("PUT", "/channels/{channel.id}/pins/{message.id}", {std::to_string(channel_id), std::to_string(message_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::unpin_message(disccord::snowflake channel_id, disccord::snowflake message_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/channels/{channel.id}/pins/{message.id}", {std::to_string(channel_id), std::to_string(message_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::add_dm_recipient(disccord::snowflake channel_id, disccord::snowflake user_id, std::string access_token, std::string nick, const pplx::cancellation_token& token)
            {
                disccord::models::rest::add_dm_recipient_args args{access_token, nick};
                auto route = build_route<2>("PUT", "/channels/{channel.id}/recipients/{user.id}", {std::to_string(channel_id), std::to_string(user_id)});
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::remove_dm_recipient(disccord::snowflake channel_id, disccord::snowflake user_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/channels/{channel.id}/recipients/{user.id}", {std::to_string(channel_id), std::to_string(user_id)});
                return request(route, token);
            }

            // Guild API
            pplx::task<disccord::models::guild> rest_api_client::get_guild(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}", {std::to_string(guild_id)});
                return request_json<disccord::models::guild>(route, token);
            }

            pplx::task<disccord::models::guild> rest_api_client::edit_guild(disccord::snowflake guild_id, disccord::models::rest::edit_guild_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("PATCH", "/guilds/{guild.id}", {std::to_string(guild_id)});
                return request_json<disccord::models::guild>(route, args, token);
            }

            pplx::task<disccord::models::guild> rest_api_client::delete_guild(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("DELETE", "/guilds/{guild.id}", {std::to_string(guild_id)});
                return request_json<disccord::models::guild>(route, token);
                }

            pplx::task<std::vector<disccord::models::channel>> rest_api_client::get_guild_channels(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/channels", {std::to_string(guild_id)});
                return request_multi_json<disccord::models::channel>(route, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::create_guild_channel(disccord::snowflake guild_id, disccord::models::rest::create_guild_channel_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/guilds/{guild.id}/channels", {std::to_string(guild_id)});
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<void> rest_api_client::edit_guild_channel_positions(disccord::snowflake guild_id, disccord::models::rest::edit_positions_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("PATCH", "/guilds/{guild.id}/channels", {std::to_string(guild_id)});
                return request_json(route, args, token);
            }

            pplx::task<disccord::models::guild_member> rest_api_client::get_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/guilds/{guild.id}/members/{user.id}", {std::to_string(guild_id), std::to_string(user_id)});
                return request_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<std::vector<disccord::models::guild_member>> rest_api_client::list_guild_members(disccord::snowflake guild_id, uint16_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("GET", "/guilds/{guild.id}/members?limit={limit}", {std::to_string(guild_id), std::to_string(limit)});
                return request_multi_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<std::vector<disccord::models::guild_member>> rest_api_client::list_guild_members_before(disccord::snowflake guild_id, disccord::snowflake user_id, uint16_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("GET", "/guilds/{guild.id}/members?before={user}&limit={limit}", {std::to_string(guild_id), std::to_string(user_id), std::to_string(limit)});
                return request_multi_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<std::vector<disccord::models::guild_member>> rest_api_client::list_guild_members_after(disccord::snowflake guild_id, disccord::snowflake user_id, uint16_t limit, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("GET", "/guilds/{guild.id}/members?after={user}&limit={limit}", {std::to_string(guild_id), std::to_string(user_id), std::to_string(limit)});
                return request_multi_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<disccord::models::guild_member> rest_api_client::add_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::models::rest::add_guild_member_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("PUT", "/guilds/{guild.id}/members/{user.id}", {std::to_string(guild_id), std::to_string(user_id)});
                return request_json<disccord::models::guild_member>(route, args, token);
            }

            pplx::task<void> rest_api_client::edit_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::models::rest::edit_guild_member_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("PATCH", "/guilds/{guild.id}/members/{user.id}", {std::to_string(guild_id), std::to_string(user_id)});
                return request_json(route, args, token);
            }

            //TODO: edit_current_nick

            pplx::task<void> rest_api_client::add_guild_member_role(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::snowflake role_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("PUT", "/guilds/{guild.id}/members/{user.id}/roles/{role.id}", {std::to_string(guild_id), std::to_string(user_id), std::to_string(role_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::remove_guild_member_role(disccord::snowflake guild_id, disccord::snowflake user_id, disccord::snowflake role_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("DELETE", "/guilds/{guild.id}/members/{user.id}/roles/{role.id}", {std::to_string(guild_id), std::to_string(user_id), std::to_string(role_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::remove_guild_member(disccord::snowflake guild_id, disccord::snowflake user_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<3>("DELETE", "/guilds/{guild.id}/members/{user.id}", {std::to_string(guild_id), std::to_string(user_id)});
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::user>> rest_api_client::get_guild_bans(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/bans", {std::to_string(guild_id)});
                return request_multi_json<disccord::models::user>(route, token);
            }

            pplx::task<void> rest_api_client::create_guild_ban(disccord::snowflake guild_id, disccord::snowflake user_id, uint8_t delete_message_days, const pplx::cancellation_token& token)
            {
                disccord::models::rest::create_guild_ban_args args{delete_message_days};
                auto route = build_route<2>("PUT", "/guilds/{guild.id}/bans/{user.id}", {std::to_string(guild_id), std::to_string(user_id)});
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::remove_guild_ban(disccord::snowflake guild_id, disccord::snowflake user_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/guilds/{guild.id}/bans/{user.id}", {std::to_string(guild_id), std::to_string(user_id)});
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::role>> rest_api_client::get_guild_roles(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/roles", {std::to_string(guild_id)});
                return request_multi_json<disccord::models::role>(route, token);
            }

            pplx::task<disccord::models::role> rest_api_client::create_guild_role(disccord::snowflake guild_id, disccord::models::rest::edit_guild_role_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("POST", "/guilds/{guild.id}/roles", {std::to_string(guild_id)});
                return request_json<disccord::models::role>(route, args, token);
            }

            pplx::task<void> rest_api_client::edit_guild_role_positions(disccord::snowflake guild_id, disccord::models::rest::edit_positions_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("PATCH", "/guilds/{guild.id}/roles", {std::to_string(guild_id)});
                return request_json(route, args, token);
            }

            pplx::task<disccord::models::role> rest_api_client::edit_guild_role(disccord::snowflake guild_id, disccord::models::rest::edit_guild_role_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("PATCH", "/guilds/{guild.id}/roles", {std::to_string(guild_id)});
                return request_json<disccord::models::role>(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_guild_role(disccord::snowflake guild_id, disccord::snowflake role_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/guilds/{guild.id}/roles/{role.id}", {std::to_string(guild_id), std::to_string(role_id)});
                return request(route, token);
            }

            //TODO: get_guild_prune_count

            //TODO: begin_guild_prune

            pplx::task<std::vector<disccord::models::voice_region>> rest_api_client::get_guild_voice_regions(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/regions", {std::to_string(guild_id)});
                return request_multi_json<disccord::models::voice_region>(route, token);
            }

            pplx::task<std::vector<disccord::models::invite>> rest_api_client::get_guild_invites(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/invites", {std::to_string(guild_id)});
                return request_multi_json<disccord::models::invite>(route, token);
            }

            pplx::task<std::vector<disccord::models::integration>> rest_api_client::get_guild_integrations(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/integrations", {std::to_string(guild_id)});
                return request_multi_json<disccord::models::integration>(route, token);
            }

            pplx::task<void> rest_api_client::create_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, std::string type, const pplx::cancellation_token& token)
            {
                disccord::models::rest::create_guild_integration_args args{integration_id, type};
                auto route = build_route<1>("PATCH", "/guilds/{guild.id}/integrations", {std::to_string(guild_id)});
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::edit_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, uint32_t expire_behavior, uint32_t expire_grace_period, bool enable_emoticons, const pplx::cancellation_token& token)
            {
                disccord::models::rest::edit_guild_integration_args args{expire_behavior, expire_grace_period, enable_emoticons};
                auto route = build_route<2>("PATCH", "/guilds/{guild.id}/integrations/{integration.id}", {std::to_string(guild_id), std::to_string(integration_id)});
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("DELETE", "/guilds/{guild.id}/integrations/{integration.id}", {std::to_string(guild_id), std::to_string(integration_id)});
                return request(route, token);
            }

            pplx::task<void> rest_api_client::sync_guild_integration(disccord::snowflake guild_id, disccord::snowflake integration_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<2>("POST", "/guilds/{guild.id}/integrations/{integration.id}/sync", {std::to_string(guild_id), std::to_string(integration_id)});
                return request(route, token);
            }

            pplx::task<disccord::models::guild_embed> rest_api_client::get_guild_embed(disccord::snowflake guild_id, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("GET", "/guilds/{guild.id}/embed", {std::to_string(guild_id)});
                return request_json<disccord::models::guild_embed>(route, token);
            }

            pplx::task<disccord::models::guild_embed> rest_api_client::edit_guild_embed(disccord::snowflake guild_id, disccord::models::rest::edit_guild_embed_args args, const pplx::cancellation_token& token)
            {
                auto route = build_route<1>("PATCH", "/guilds/{guild.id}/embed", {std::to_string(guild_id)});
                return request_json<disccord::models::guild_embed>(route, args, token);
            }

            // Voice API
            pplx::task<std::vector<disccord::models::voice_region>> rest_api_client::list_voice_regions(const pplx::cancellation_token& token)
            {
                auto route = build_route<0>("GET", "/voice/regions", {});
                return request_multi_json<disccord::models::voice_region>(route, token);
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
                        case disccord::token_type::BEARER:
                            token_type_s = "Bearer ";
                            break;
                        case disccord::token_type::BOT:
                            token_type_s = "Bot ";
                            break;
                        case disccord::token_type::USER:
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
