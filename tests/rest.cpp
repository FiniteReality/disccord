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

    if (token.empty())
    {
        FAIL("Pass a **BOT** token through the environment variable `DISCCORD_TEST_TOKEN`");
    }

    if (user_id.empty())
    {
        WARN("No userid was passed, using default");
        user_id = "257584807716978688";
    }

    uint64_t id = std::stoull(user_id);

    GIVEN("an api client with our token and id") {
        auto api_client = rest_api_client(web::uri("https://discordapp.com/api/v6"), token, disccord::token_type::Bot);

        WHEN("we retrieve the current user") {
            uint64_t retrieved_id;

            api_client.get_current_user().then([&](user ent)
            {
                CAPTURE(ent.get_id());
                retrieved_id = ent.get_id();
            }).wait();

            THEN("the id equals what we are given") {
                REQUIRE(retrieved_id == id);
            }
        }

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

            disccord::rest::models::create_message_args args{message_builder.str()};

            bool success;

            api_client.create_message(237990708101775361, args).then([&](pplx::task<message> message_task)
            {
                try
                {
                    auto message = message_task.wait();
                    success = true;
                }
                catch (std::exception e)
                {
                    WARN("create_message failed with" << e.what());
                    success = false;
                }
            }).wait();

            THEN("the send succeeds") {
                if (!success)
                    WARN("create_message failed!");
                REQUIRE(success);
            }
        }
    }
}
