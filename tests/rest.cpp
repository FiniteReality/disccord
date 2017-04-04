#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <rest/api_client.hpp>
#include <rest/route.hpp>
#include <disccord.hpp>

#include <models/user.hpp>

#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>

using namespace disccord::rest::internal;
using namespace disccord::models;

std::string environment_variable(std::string name)
{
    if (const char* contents = std::getenv(name.c_str()))
    {
        return std::string(contents);
    }
    else
    {
        return "";
    }
}

SCENARIO("REST api is successful", "[!mayfail]") {
    std::string token = environment_variable("DISCCORD_TEST_TOKEN");
    std::string user_id = environment_variable("DISCCORD_TEST_USER_ID");
    std::string channel_id = environment_variable("DISCCORD_TEST_CHANNEL_ID");
    std::string guild_id = environment_variable("DISCCORD_TEST_GUILD_ID");
    std::string invite_code = environment_variable("DISCCORD_TEST_INVITE_CODE");

    if (token.empty())
    {
        FAIL("Pass a **BOT** token through the environment variable `DISCCORD_TEST_TOKEN`");
    }

    if (user_id.empty())
    {
        WARN("No userid was passed, using default");
        user_id = "257584807716978688";
    }
    
    if (channel_id.empty())
    {
        WARN("No channelid was passed, using default");
        channel_id = "237990708101775361";
    }
    
    if (guild_id.empty())
    {
        WARN("No guildid was passed, using default");
        guild_id = "226692368148070420";
    }
    
    if (invite_code.empty())
    {
        WARN("No invitecode was passed, using default");
        invite_code = "Kqp5sYQ"; //this is a code set to never expire for disccord's guild.
    }

    uint64_t u_id = std::stoull(user_id);
    uint64_t c_id = std::stoull(channel_id);
    uint64_t g_id = std::stoull(guild_id);
    bool req_success; //keep track of requests success state.

    GIVEN("an api client with our token and id") {
        auto api_client = rest_api_client(web::uri("https://discordapp.com/api/v6"), token, disccord::token_type::Bot);

        // User API tests
        WHEN("we retrieve the current user") {
            uint64_t retrieved_id;

            api_client.get_current_user().then([&](user ent)
            {
                CAPTURE(ent.get_id());
                retrieved_id = ent.get_id();
            }).wait();

            THEN("the id equals what we are given") {
                REQUIRE(retrieved_id == u_id);
            }
        }

        // Channel API tests
        WHEN("we send a message") {
            std::stringstream message_builder;

            message_builder
            << "Hello, world! Message sent using disccord "
            << DISCCORD_VERSION
            << " located at <"
            << DISCCORD_PROJECT_URL
            << ">!" << "\n";

            std::string ci_id = environment_variable("TRAVIS_BUILD_NUMBER");
            std::string ci_commit = environment_variable("TRAVIS_COMMIT");
            std::string compiler = environment_variable("CXX");

            if (ci_id != "")
            {
                message_builder
                << "**Build ID:** " << ci_id << "\n"
                << "**Commit:** " << ci_commit << "\n"
                << "**Compiler:** " << compiler << "\n";
            }

            api_client.create_message(c_id, message_builder.str()).then([&](message msg)
            {
                req_success = true;
            }).wait();

            THEN("the send succeeds") {
                if (!req_success)
                    FAIL("create_message failed!");
                req_success = false;
            }
        }
        
        // Invite API tests
        
        // Guild API tests
        WHEN("We get a guild") {
            
            api_client.get_guild(g_id).then([&](guild gd)
            {
                REQUIRE(gd.get_id() == g_id);
                req_success = true;
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild failed!");
                req_success = false;
            }
        }
        
        WHEN("We get a guilds channels") {
            
            api_client.get_guild_channels(g_id).then([&](std::vector<channel> channels)
            {
                req_success = true;
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_channels failed!");
                req_success = false;
            }
        }
    }
}
