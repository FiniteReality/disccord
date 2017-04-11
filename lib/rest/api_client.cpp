#include <type_traits>

#include <disccord/rest/api_client.hpp>
#include <disccord/rest.hpp>

#include <disccord/rest/models/add_guild_member_args.hpp>
#include <disccord/rest/models/create_dm_channel_args.hpp>
#include <disccord/rest/models/create_group_dm_args.hpp>
#include <disccord/rest/models/create_guild_ban_args.hpp>
#include <disccord/rest/models/create_guild_channel_args.hpp>
#include <disccord/rest/models/create_guild_integration_args.hpp>
#include <disccord/rest/models/create_message_args.hpp>
#include <disccord/rest/models/guild_role_args.hpp>
#include <disccord/rest/models/modify_guild_args.hpp>
#include <disccord/rest/models/modify_guild_embed_args.hpp>
#include <disccord/rest/models/modify_guild_integration_args.hpp>
#include <disccord/rest/models/modify_guild_member_args.hpp>
#include <disccord/rest/models/modify_positions_args.hpp>
#include <disccord/rest/models/bulk_delete_message_args.hpp>
#include <disccord/rest/models/edit_channel_permissions_args.hpp>
#include <disccord/rest/models/add_dm_recipient_args.hpp>
#include <disccord/rest/models/modify_current_nick_args.hpp>

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

                return bucket->enter(http_client, request, token);
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

            pplx::task<web::json::value> rest_api_client::request_raw_json(route_info& route, const pplx::cancellation_token& token)
            {
                return request_internal(route, token).then([](web::http::http_response response)
                {
                    return response.extract_json();
                }).then([](web::json::value response)
                {
                    return response;
                });
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

            pplx::task<disccord::models::user> rest_api_client::modify_current_user(disccord::rest::models::modify_current_user_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/users/@me");
                return request_json<disccord::models::user>(route, args, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds(uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/guilds?limit={limit}", std::to_string(limit));
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds_before(uint64_t guild_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/guilds?before={guild}&limit={limit}", std::to_string(guild_id), std::to_string(limit));
                return request_multi_json<disccord::models::user_guild>(route, token);
            }

            pplx::task<std::vector<disccord::models::user_guild>> rest_api_client::get_current_user_guilds_after(uint64_t guild_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/users/@me/guilds?after={guild}&limit={limit}", std::to_string(guild_id), std::to_string(limit));
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
            pplx::task<disccord::models::channel> rest_api_client::get_channel(uint64_t channel_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}", std::to_string(channel_id));
                return request_json<disccord::models::channel>(route, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::modify_channel(uint64_t channel_id, disccord::rest::models::modify_channel_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/channels/{channel.id}", std::to_string(channel_id));
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::delete_channel(uint64_t channel_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}", std::to_string(channel_id));
                return request_json<disccord::models::channel>(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_channel_messages(uint64_t channel_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/messages?limit={limit}", std::to_string(channel_id), std::to_string(limit));
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_channel_messages_before(uint64_t channel_id, uint64_t message_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/messages?before={message}&limit=limit", std::to_string(channel_id), std::to_string(message_id));
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_channel_messages_after(uint64_t channel_id, uint64_t message_id, uint8_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/messages?after={message}&limit={limit}", std::to_string(channel_id), std::to_string(message_id), std::to_string(limit));
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<disccord::models::message> rest_api_client::get_message(uint64_t channel_id, uint64_t message_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/messages/{message_id}", std::to_string(channel_id), std::to_string(message_id));
                return request_json<disccord::models::message>(route, token);
            }

            pplx::task<disccord::models::message> rest_api_client::create_message(uint64_t channel_id, disccord::rest::models::create_message_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/channels/{channel.id}/messages", std::to_string(channel_id));
                return request_json<disccord::models::message>(route, args, token);
            }

            pplx::task<disccord::models::message> rest_api_client::create_message(uint64_t channel_id, disccord::api::multipart_request args, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/channels/{channel.id}/messages", std::to_string(channel_id));
                return request_multipart<disccord::models::message>(route, args, token);
            }

            pplx::task<void> rest_api_client::create_reaction(uint64_t channel_id, uint64_t message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = get_route("PUT", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me", std::to_string(channel_id), std::to_string(message_id), emoji);
                return request(route, token);
            }

            pplx::task<void> rest_api_client::delete_own_reaction(uint64_t channel_id, uint64_t message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me", std::to_string(channel_id), emoji, std::to_string(message_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::delete_user_reaction(uint64_t channel_id, uint64_t message_id, uint64_t user_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user_id}", std::to_string(channel_id), std::to_string(message_id), emoji, std::to_string(user_id));
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::user>> rest_api_client::get_reactions(uint64_t channel_id, uint64_t message_id, std::string emoji, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}", std::to_string(channel_id), std::to_string(message_id), emoji);
                return request_multi_json<disccord::models::user>(route, token);
            }

            pplx::task<void> rest_api_client::delete_all_reactions(uint64_t channel_id, uint64_t message_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/messages/{message.id}/reactions", std::to_string(channel_id), std::to_string(message_id));
                return request(route, token);
            }

            pplx::task<disccord::models::message> rest_api_client::edit_message(uint64_t channel_id, uint64_t message_id, disccord::rest::models::edit_message_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/channels/{channel.id}/messages/{message_id}", std::to_string(channel_id), std::to_string(message_id));
                return request_json<disccord::models::message>(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_message(uint64_t channel_id, uint64_t message_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/messages/{message.id}", std::to_string(channel_id), std::to_string(message_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::bulk_delete_messages(uint64_t channel_id, std::vector<uint64_t> message_ids, const pplx::cancellation_token& token)
            {
                disccord::rest::models::bulk_delete_message_args args{message_ids};
                auto route = get_route("DELETE", "/channels/{channel.id}/messages/bulk-delete", std::to_string(channel_id));
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::edit_channel_permissions(uint64_t channel_id, uint64_t overwrite_id, uint32_t allow, uint32_t deny, std::string type, const pplx::cancellation_token& token)
            {
                disccord::rest::models::edit_channel_permissions_args args{allow, deny, type};
                auto route = get_route("PUT", "/channels/{channel.id}/permissions/{overwrite_id}", std::to_string(channel_id), std::to_string(overwrite_id));
                return request_json(route, args, token);
            }

            pplx::task<std::vector<disccord::models::invite>> rest_api_client::get_channel_invites(uint64_t channel_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/invites", std::to_string(channel_id));
                return request_multi_json<disccord::models::invite>(route, token);
            }

            pplx::task<disccord::models::invite> rest_api_client::create_channel_invite(uint64_t channel_id, disccord::rest::models::create_channel_invite_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/channels/{channel.id}/invites", std::to_string(channel_id));
                return request_json<disccord::models::invite>(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_channel_permissions(uint64_t channel_id, uint64_t overwrite_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/permissions/{overwrite_id}", std::to_string(channel_id), std::to_string(overwrite_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::trigger_typing(uint64_t channel_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/channels/{channel.id}/typing", std::to_string(channel_id));
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::message>> rest_api_client::get_pinned_messages(uint64_t channel_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/channels/{channel.id}/pins", std::to_string(channel_id));
                return request_multi_json<disccord::models::message>(route, token);
            }

            pplx::task<void> rest_api_client::pin_message(uint64_t channel_id, uint64_t message_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("PUT", "/channels/{channel.id}/pins/{message_id}", std::to_string(channel_id), std::to_string(message_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::unpin_message(uint64_t channel_id, uint64_t message_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/pins/{message_id}", std::to_string(channel_id), std::to_string(message_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::add_dm_recipient(uint64_t channel_id, uint64_t user_id, std::string access_token, std::string nick, const pplx::cancellation_token& token)
            {
                disccord::rest::models::add_dm_recipient_args args{access_token, nick};
                auto route = get_route("PUT", "/channels/{channel.id}/recipients/{user_id}", std::to_string(channel_id), std::to_string(user_id));
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::remove_dm_recipient(uint64_t channel_id, uint64_t user_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/channels/{channel.id}/recipients/{user_id}", std::to_string(channel_id), std::to_string(user_id));
                return request(route, token);
            }

            // Guild API
            pplx::task<disccord::models::guild> rest_api_client::get_guild(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}", std::to_string(guild_id));
                return request_json<disccord::models::guild>(route, token);
            }

            pplx::task<disccord::models::guild> rest_api_client::modify_guild(uint64_t guild_id, disccord::rest::models::modify_guild_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/guilds/{guild.id}", std::to_string(guild_id));
                return request_json<disccord::models::guild>(route, args, token);
            }

            pplx::task<disccord::models::guild> rest_api_client::delete_guild(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/guilds/{guild.id}", std::to_string(guild_id));
                return request_json<disccord::models::guild>(route, token);
                }

            pplx::task<std::vector<disccord::models::channel>> rest_api_client::get_guild_channels(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/channels", std::to_string(guild_id));
                return request_multi_json<disccord::models::channel>(route, token);
            }

            pplx::task<disccord::models::channel> rest_api_client::create_guild_channel(uint64_t guild_id, disccord::rest::models::create_guild_channel_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/guilds/{guild.id}/channels", std::to_string(guild_id));
                return request_json<disccord::models::channel>(route, args, token);
            }

            pplx::task<void> rest_api_client::modify_guild_channel_positions(uint64_t guild_id, disccord::rest::models::modify_positions_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/guilds/{guild.id}/channels", std::to_string(guild_id));
                return request_json(route, args, token);
            }

            pplx::task<disccord::models::guild_member> rest_api_client::get_guild_member(uint64_t guild_id, uint64_t user_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/members/{user.id}", std::to_string(guild_id), std::to_string(user_id));
                return request_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<std::vector<disccord::models::guild_member>> rest_api_client::list_guild_members(uint64_t guild_id, uint16_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/members?limit={limit}", std::to_string(guild_id), std::to_string(limit));
                return request_multi_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<std::vector<disccord::models::guild_member>> rest_api_client::list_guild_members_before(uint64_t guild_id, uint64_t user_id, uint16_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/members?before={user}&limit={limit}", std::to_string(guild_id), std::to_string(user_id));
                return request_multi_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<std::vector<disccord::models::guild_member>> rest_api_client::list_guild_members_after(uint64_t guild_id, uint64_t user_id, uint16_t limit, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/members?after={user}&limit={limit}", std::to_string(guild_id), std::to_string(user_id), std::to_string(limit));
                return request_multi_json<disccord::models::guild_member>(route, token);
            }

            pplx::task<disccord::models::guild_member> rest_api_client::add_guild_member(uint64_t guild_id, uint64_t user_id, disccord::rest::models::add_guild_member_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PUT", "/guilds/{guild.id}/members/{user.id}", std::to_string(guild_id), std::to_string(user_id));
                return request_json<disccord::models::guild_member>(route, args, token);
            }

            pplx::task<void> rest_api_client::modify_guild_member(uint64_t guild_id, uint64_t user_id, disccord::rest::models::modify_guild_member_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/guilds/{guild.id}/members/{user.id}", std::to_string(guild_id), std::to_string(user_id));
                return request_json(route, args, token);
            }

            pplx::task<web::json::value> rest_api_client::modify_current_nick(uint64_t guild_id, std::string nick, const pplx::cancellation_token& token)
            {
                disccord::rest::models::modify_current_nick_args args(nick);
                auto route = get_route("PATCH", "/guilds/{guild.id}/members/@me/nick", std::to_string(guild_id));
                return request_raw_json(route, args, token);
            }

            pplx::task<void> rest_api_client::add_guild_member_role(uint64_t guild_id, uint64_t user_id, uint64_t role_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("PUT", "/guilds/{guild.id}/members/{user.id}/roles/{role.id}", std::to_string(guild_id), std::to_string(user_id), std::to_string(role_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::remove_guild_member_role(uint64_t guild_id, uint64_t user_id, uint64_t role_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/guilds/{guild.id}/members/{user.id}/roles/{role.id}", std::to_string(guild_id), std::to_string(user_id), std::to_string(role_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::remove_guild_member(uint64_t guild_id, uint64_t user_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/guilds/{guild.id}/members/{user.id}", std::to_string(guild_id), std::to_string(user_id));
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::user>> rest_api_client::get_guild_bans(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/bans", std::to_string(guild_id));
                return request_multi_json<disccord::models::user>(route, token);
            }

            pplx::task<void> rest_api_client::create_guild_ban(uint64_t guild_id, uint64_t user_id, uint8_t delete_message_days, const pplx::cancellation_token& token)
            {
                disccord::rest::models::create_guild_ban_args args{delete_message_days};
                auto route = get_route("PUT", "/guilds/{guild.id}/bans/{user.id}", std::to_string(guild_id), std::to_string(user_id));
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::remove_guild_ban(uint64_t guild_id, uint64_t user_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/guilds/{guild.id}/bans/{user.id}", std::to_string(guild_id), std::to_string(user_id));
                return request(route, token);
            }

            pplx::task<std::vector<disccord::models::role>> rest_api_client::get_guild_roles(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/roles", std::to_string(guild_id));
                return request_multi_json<disccord::models::role>(route, token);
            }

            pplx::task<disccord::models::role> rest_api_client::create_guild_role(uint64_t guild_id, disccord::rest::models::guild_role_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/guilds/{guild.id}/roles", std::to_string(guild_id));
                return request_json<disccord::models::role>(route, args, token);
            }

            pplx::task<void> rest_api_client::modify_guild_role_positions(uint64_t guild_id, disccord::rest::models::modify_positions_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/guilds/{guild.id}/roles", std::to_string(guild_id));
                return request_json(route, args, token);
            }

            pplx::task<disccord::models::role> rest_api_client::modify_guild_role(uint64_t guild_id, disccord::rest::models::guild_role_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/guilds/{guild.id}/roles", std::to_string(guild_id));
                return request_json<disccord::models::role>(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_guild_role(uint64_t guild_id, uint64_t role_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/guilds/{guild.id}/roles/{role.id}", std::to_string(guild_id), std::to_string(role_id));
                return request(route, token);
            }

            pplx::task<web::json::value> rest_api_client::get_guild_prune_count(uint64_t guild_id, uint32_t days, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/prune?days={days}", std::to_string(guild_id), std::to_string(days));
                return request_raw_json(route, token);
            }

            pplx::task<web::json::value> rest_api_client::begin_guild_prune(uint64_t guild_id, uint32_t days, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/guilds/{guild.id}/prune?days={days}", std::to_string(guild_id), std::to_string(days));
                return request_raw_json(route, token);
            }

            pplx::task<std::vector<disccord::models::voice_region>> rest_api_client::get_guild_voice_regions(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/regions", std::to_string(guild_id));
                return request_multi_json<disccord::models::voice_region>(route, token);
            }

            pplx::task<std::vector<disccord::models::invite>> rest_api_client::get_guild_invites(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/invites", std::to_string(guild_id));
                return request_multi_json<disccord::models::invite>(route, token);
            }

            pplx::task<std::vector<disccord::models::integration>> rest_api_client::get_guild_integrations(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/integrations", std::to_string(guild_id));
                return request_multi_json<disccord::models::integration>(route, token);
            }

            pplx::task<void> rest_api_client::create_guild_integration(uint64_t guild_id, uint64_t integration_id, std::string type, const pplx::cancellation_token& token)
            {
                disccord::rest::models::create_guild_integration_args args{type, integration_id};
                auto route = get_route("PATCH", "/guilds/{guild.id}/integrations", std::to_string(guild_id));
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::modify_guild_integration(uint64_t guild_id, uint64_t integration_id, uint32_t expire_behavior, uint32_t expire_grace_period, bool enable_emoticons, const pplx::cancellation_token& token)
            {
                disccord::rest::models::modify_guild_integration_args args{expire_behavior, expire_grace_period, enable_emoticons};
                auto route = get_route("PATCH", "/guilds/{guild.id}/integrations/{integration.id}", std::to_string(guild_id), std::to_string(integration_id));
                return request_json(route, args, token);
            }

            pplx::task<void> rest_api_client::delete_guild_integration(uint64_t guild_id, uint64_t integration_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("DELETE", "/guilds/{guild.id}/integrations/{integration.id}", std::to_string(guild_id), std::to_string(integration_id));
                return request(route, token);
            }

            pplx::task<void> rest_api_client::sync_guild_integration(uint64_t guild_id, uint64_t integration_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("POST", "/guilds/{guild.id}/integrations/{integration.id}/sync", std::to_string(guild_id), std::to_string(integration_id));
                return request(route, token);
            }

            pplx::task<disccord::models::guild_embed> rest_api_client::get_guild_embed(uint64_t guild_id, const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/guilds/{guild.id}/embed", std::to_string(guild_id));
                return request_json<disccord::models::guild_embed>(route, token);
            }

            pplx::task<disccord::models::guild_embed> rest_api_client::modify_guild_embed(uint64_t guild_id, disccord::rest::models::modify_guild_embed_args args, const pplx::cancellation_token& token)
            {
                auto route = get_route("PATCH", "/guilds/{guild.id}/embed", std::to_string(guild_id));
                return request_json<disccord::models::guild_embed>(route, args, token);
            }

            // Voice API
            pplx::task<std::vector<disccord::models::voice_region>> rest_api_client::list_voice_regions(const pplx::cancellation_token& token)
            {
                auto route = get_route("GET", "/voice/regions");
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
