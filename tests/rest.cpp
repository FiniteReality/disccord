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

//TODO: will probably split off each api resource(User, Invite, Guild, Channel) into their own respective files
//with their own scenario. but for now, keeping it like this. will most likely create a test class as well
//that has resources like environment_variable() to set all needed id's, this can be shared throughout all the test files.
SCENARIO("REST api is successful", "[!mayfail]") {
    std::string token = environment_variable("DISCCORD_TEST_TOKEN");
    std::string user_id = environment_variable("DISCCORD_TEST_USER_ID");
    std::string channel_id = environment_variable("DISCCORD_TEST_CHANNEL_ID");
    std::string guild_id = environment_variable("DISCCORD_TEST_GUILD_ID");
    std::string invite_code = environment_variable("DISCCORD_TEST_INVITE_CODE");
    std::string role_id = environment_variable("DISCCORD_TEST_ROLE_ID");
    
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
    
    if (role_id.empty())
    {
        WARN("No roleid was passed, using default");
        role_id = "226692368148070420"; //this isnt an actual role id on disccord right now.
    }

    uint64_t u_id = std::stoull(user_id);
    uint64_t c_id = std::stoull(channel_id);
    uint64_t g_id = std::stoull(guild_id);
    uint64_t r_id = std::stoull(role_id);
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

            api_client.create_message(c_id, message_builder.str()).then([&](pplx::task<message> message_task)
            {
                try
                {
                    auto message = message_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the send succeeds") {
                if (!req_success)
                    WARN("create_message failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        
        // Invite API tests
        
        // Guild API tests
        WHEN("We get a guild") {
            
            api_client.get_guild(g_id).then([&](pplx::task<guild> guild_task)
            {
                try
                {
                    auto guild = guild_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We get a guilds channels") {
            
            api_client.get_guild_channels(g_id).then([&](pplx::task<std::vector<channel>> channels_task)
            {
                try
                {
                    auto guild = channels_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_channels failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        /* WHEN("We modify channel positions") {
            
            std::pair<uint64_t, uint8_t> pos1(c_id, 3);
            std::pair<uint64_t, uint8_t> pos2(g_id, 2); //general channel
            std::vector<std::pair<uint64_t, uint8_t>> params = {pos1, pos2};
            
            api_client.modify_guild_channel_positions(g_id, params).then([&](pplx::task<std::vector<channel>> channels_task)
            {
                try
                {
                    auto guild = channels_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("modify_guild_channel_positions failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        } */
        WHEN("We get a guild member") {
            
            api_client.get_guild_member(g_id, u_id).then([&](pplx::task<disccord::models::guild_member> member_task)
            {
                try
                {
                    auto guild = member_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_member failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We list a guilds members") {
            
            api_client.list_guild_members(g_id).then([&](pplx::task<std::vector<guild_member>> members_task)
            {
                try
                {
                    auto guild = members_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_channels failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        //add the other overloads here
        
        WHEN("We add a guild member role") {
            
            api_client.add_guild_member_role(g_id, u_id, r_id).then([&](pplx::task<void> add_role_task)
            {
                try
                {
                    add_role_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("add_guild_member_role failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We remove a guild member role") {
            
            api_client.remove_guild_member_role(g_id, u_id, r_id).then([&](pplx::task<void> rm_role_task)
            {
                try
                {
                    rm_role_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("remove_guild_member_role failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We get guild bans") {
            
            api_client.get_guild_bans(g_id).then([&](pplx::task<std::vector<disccord::models::user>> users_task)
            {
                try
                {
                    users_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_bans failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We create a guild ban") {
            
            api_client.create_guild_ban(g_id, 299480849865506816, 0).then([&](pplx::task<void> ban_task)
            {
                try
                {
                    ban_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("create_guild_ban failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We remove a guild ban") {
            
            api_client.remove_guild_ban(g_id, 299480849865506816).then([&](pplx::task<void> unban_task)
            {
                try
                {
                    unban_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("remove_guild_ban failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We get guild roles") {
            
            api_client.get_guild_roles(g_id).then([&](pplx::task<std::vector<disccord::models::role>> roles_task)
            {
                try
                {
                    roles_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_roles failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        // add missing tests here
        
        WHEN("We get guild invites") {
            
            api_client.get_guild_invites(g_id).then([&](pplx::task<std::vector<disccord::models::invite>> invites_task)
            {
                try
                {
                    invites_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_invites failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We get guild integrations") {
            
            api_client.get_guild_integrations(g_id).then([&](pplx::task<std::vector<disccord::models::integration>> integrations_task)
            {
                try
                {
                    integrations_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_integrations failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
        WHEN("We get the guild embed") {
            
            api_client.get_guild_embed(g_id).then([&](pplx::task<disccord::models::guild_embed> gd_embed_task)
            {
                try
                {
                    gd_embed_task.wait();
                    req_success = true;
                }
                catch (...)
                {
                    req_success = false;
                }
            }).wait();

            THEN("the req succeeds") {
                if (!req_success)
                    FAIL("get_guild_embed failed!");
                REQUIRE(req_success);
                req_success = false;
            }
        }
    }
}
