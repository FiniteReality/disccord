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

TEST_CASE( "Correct entity ids are returned", "[!throws]" ) {
    std::string token = environment_variable("DISCCORD_TEST_TOKEN");
    std::string user_id = environment_variable("DISCCORD_TEST_USER_ID");

    if (token.empty())
    {
        throw std::runtime_error("Pass a **BOT** token through the environment variable `DISCCORD_TEST_TOKEN`");
    }

    if (user_id.empty())
    {
        WARN("No userid was passed, using default");
        user_id = "257584807716978688";
    }

    uint64_t id = std::stoull(user_id);

    auto api_client = rest_api_client(web::uri("https://discordapp.com/api/v6"), token, disccord::token_type::Bot);

    api_client.get_current_user().then([=](user ent)
    {
        CAPTURE(ent.get_id());
        REQUIRE(ent.get_id() == id);
    }).wait();

    std::stringstream message_builder;

    message_builder
    << "Hello, world! Message sent using disccord "
    << DISCCORD_VERSION
    << " located at <"
    << DISCCORD_PROJECT_URL
    << ">!" << "\n";

    std::string ci_id = environment_variable("TRAVIS_BUILD_NUMBER");
    std::string ci_commit = environment_variable("TRAVIS_COMMIT");

    if (ci_id != "")
    {
        message_builder
        << "**Build ID:** " << ci_id << "\n"
        << "**Commit:** " << ci_commit << "\n";
    }

    bool success;

    api_client.create_message(237990708101775361, message_builder.str()).then([&](message msg)
    {
        success = true;
    }).wait();

    if (!success)
        FAIL("create_message failed!");
}
