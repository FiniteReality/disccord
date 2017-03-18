#ifndef _rest_api_client_hpp_
#define _rest_api_client_hpp_

#include <cpprest/http_client.h>

#include <rest/route.hpp>
#include <api/bucket_info.hpp>
#include <token_type.hpp>

#include <models/user.hpp>
#include <models/user_guild.hpp>
#include <models/channel.hpp>
#include <models/connection.hpp>

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

                    // Declared here because of silly C++ requirements
                    template <typename T>
                    pplx::task<T> request(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        auto bucket = get_bucket(route);

                        auto base_url = http_client.base_uri().to_string();
                        
                        return bucket->request(http_client, route.full_url).then([=](web::json::value content){
                            T value;
                            value.decode(content);
                            return value;
                        });
                    }
                    
                    template <typename T>
                    pplx::task<T> request(route_info& route, web::json::value body, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        auto bucket = get_bucket(route);

                        auto base_url = http_client.base_uri().to_string();
                        
                        return bucket->request(http_client, route.full_url, body).then([=](web::json::value content){
                            T value;
                            value.decode(content);
                            return value;
                        });
                    }
                    
                    // TODO: find a way to generalize the request method to do std::vector<ModelType> or just ModelType
                    // (in a way where the compiler will be happy), then this logic can be merged into the above method.
                    // NOTE: this method should only be used if T = std::vector<ModelType>
                    template <typename T>
                    pplx::task<T> request_array(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        auto bucket = get_bucket(route);

                        auto base_url = http_client.base_uri().to_string();
                        
                        return bucket->request(http_client, route.full_url).then([=](web::json::value content){
                            T value;
                            
                            if (content.is_array()){ 
                                for (auto i : content.as_array()){
                                    typename T::value_type obj;
                                    obj.decode(i);
                                    value.push_back(obj);
                                }
                            }
                            // Incase for some reason the api doesn't return an array, we still want to treat it like they did 
                            else { 
                                typename T::value_type obj;
                                obj.decode(content);
                                std::vector<typename T::value_type> temp;
                                temp.push_back(obj);
                                value = temp;
                            }
                            return value;
                        });
                    }
                    
                    template <typename T>
                    pplx::task<T> request_array(route_info& route, web::json::value body, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        auto bucket = get_bucket(route);

                        auto base_url = http_client.base_uri().to_string();
                        
                        return bucket->request(http_client, route.full_url, body).then([=](web::json::value content){
                            T value;
                            
                            if (content.is_array()){ 
                                for (auto i : content.as_array()){
                                    typename T::value_type obj;
                                    obj.decode(i);
                                    value.push_back(obj);
                                }
                            }
                            // Incase for some reason the api doesn't return an array, we still want to treat it like they did 
                            else { 
                                typename T::value_type obj;
                                obj.decode(content);
                                value.push_back(obj);
                            }
                            return value;
                        });
                    }
                    
                    // User API
                    pplx::task<disccord::models::user> get_current_user(pplx::cancellation_token token = pplx::cancellation_token::none());
                    
                    pplx::task<disccord::models::user> get_user(uint64_t user_id, 
                                                                pplx::cancellation_token token = pplx::cancellation_token::none());
                    
                    pplx::task<disccord::models::user> modify_current_user(std::string username, 
                                                                            pplx::cancellation_token token = pplx::cancellation_token::none());
                    //avatar format: data:image/jpeg;base64,MY_BASE64_IMAGE_DATA_HERE, maybe should make an object for Avatars (models::avatar)?? thoughts
                    /* pplx::task<disccord::models::user> modify_current_user(std::string avatar, 
                                                                            pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<disccord::models::user> modify_current_user(std::string username, std::string avatar, 
                                                                            pplx::cancellation_token token = pplx::cancellation_token::none()); */
                    
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(uint8_t limit, 
                                                                                pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(std::string query, uint64_t guild_id,  //query can be either "before" or "after".
                                                                                pplx::cancellation_token token = pplx::cancellation_token::none());
                    pplx::task<std::vector<disccord::models::user_guild>> get_current_user_guilds(std::string query, uint64_t guild_id, uint8_t limit, 
                                                                                pplx::cancellation_token token = pplx::cancellation_token::none());
                                                                                
                    pplx::task<void> leave_guild(uint64_t guild_id, 
                                                pplx::cancellation_token token = pplx::cancellation_token::none());
                                                                        
                    pplx::task<std::vector<disccord::models::channel>> get_user_dms(pplx::cancellation_token token = pplx::cancellation_token::none());
                    
                    pplx::task<disccord::models::channel> create_dm(uint64_t recipient_id, 
                                                                    pplx::cancellation_token token = pplx::cancellation_token::none());
                     
                    pplx::task<disccord::models::channel> create_group_dm(std::vector<std::string> access_tokens, web::json::value nicks,
                                                                        pplx::cancellation_token token = pplx::cancellation_token::none());
                    
                    pplx::task<std::vector<disccord::models::connection>> get_user_connections(pplx::cancellation_token token = pplx::cancellation_token::none());
                    
                private:
                    disccord::api::bucket_info* get_bucket(route_info& route);

                    web::http::client::http_client http_client;
                    std::unordered_map<std::string, disccord::api::bucket_info*> buckets;
                    std::string token;
                    disccord::token_type token_type;
                    void setup_discord_handler();
            };
        }
    }
}

#endif /* _rest_client_hpp_ */