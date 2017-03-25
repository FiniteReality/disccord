#ifndef _rest_api_client_hpp_
#define _rest_api_client_hpp_

#include <cpprest/http_client.h>

#include <rest/route.hpp>
#include <api/bucket_info.hpp>
#include <api/multipart_request.hpp>
#include <token_type.hpp>

#include <models/user.hpp>
#include <models/user_guild.hpp>
#include <models/channel.hpp>
#include <models/connection.hpp>
#include <models/invite.hpp>

#include <unordered_map>
#include <vector>

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

                    // User API
                    pplx::task<disccord::models::user> get_current_user(pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::user> get_user(uint64_t user_id, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::user> modify_current_user(std::string username, pplx::cancellation_token token = pplx::cancellation_token::none());
                    //avatar format: data:image/jpeg;base64,MY_BASE64_IMAGE_DATA_HERE, maybe should make an object for Avatars (models::avatar)?? thoughts
                    /* pplx::task<disccord::models::user> modify_current_user(std::string avatar, 
                                                                            pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<disccord::models::user> modify_current_user(std::string username, std::string avatar, 
                                                                            pplx::cancellation_token token = pplx::cancellation_token::none()); */

                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(uint8_t limit, pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(std::string query, uint64_t guild_id, pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(std::string query, uint64_t guild_id, uint8_t limit, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<void> leave_guild(uint64_t guild_id, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::channel>> get_user_dms(pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_dm_channel(uint64_t recipient_id, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::channel> create_group_dm(std::unordered_map<uint64_t, std::string> nicks, std::vector<std::string> access_tokens, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<std::vector<disccord::models::connection>> get_user_connections(pplx::cancellation_token token = pplx::cancellation_token::none());

                    // Invite API
                    pplx::task<disccord::models::invite> get_invite(std::string invite_code, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> delete_invite(std::string invite_code, pplx::cancellation_token token = pplx::cancellation_token::none());

                    pplx::task<disccord::models::invite> accept_invite(std::string invite_code, pplx::cancellation_token token = pplx::cancellation_token::none());

                private:
                    pplx::task<web::http::http_response> request_internal(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<web::http::http_response> request_internal(route_info& route, disccord::api::request_info* request, pplx::cancellation_token token = pplx::cancellation_token::none());
                    disccord::api::bucket_info* get_bucket(route_info& route);

                    web::http::client::http_client http_client;
                    std::unordered_map<std::string, disccord::api::bucket_info*> buckets;
                    std::string token;
                    disccord::token_type token_type;
                    void setup_discord_handler();

                    template <typename TResponse>
                    pplx::task<TResponse> request_json(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none())
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
                    pplx::task<TResponse> request_json(route_info& route, TModel body, pplx::cancellation_token token = pplx::cancellation_token::none())
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

                    template <typename TResponse>
                    pplx::task<std::vector<TResponse>> request_multi_json(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none())
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
                    pplx::task<std::vector<TResponse>> request_multi_json(route_info& route, std::vector<TModel> body, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        web::json::array body_arr(body.size());
                        std::transform(body.begin(), body.end(), body_arr.size(), [](TModel value)
                        {
                            return value.encode();
                        });

                        web::json::value _body = body_arr;

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

                    template <typename TResponse>
                    pplx::task<TResponse> request_multipart(route_info& route, disccord::api::multipart_request args, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        disccord::api::request_info* info = new disccord::api::request_info();

                        info->set_body(args.encode(), args.get_content_type());
                        return request_internal(route, info, token).then([](web::http::http_response response)
                        {
                            return response.extract_string();
                        }).then([](std::string response)
                        {
                            TResponse result;
                            result.decode_string(response);
                            return result;
                        });
                    }
            };
        }
    }
}

#endif /* _rest_client_hpp_ */
