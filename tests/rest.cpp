#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <rest/api_client.hpp>
#include <rest/route.hpp>

#include <models/user.hpp>

#include <iostream>
#include <fstream>

#include <cstdlib>

using namespace disccord::rest::internal;
using namespace disccord::models;

std::string environment_variable(std::string name)
{
	if (const char* contents = std::getenv(name.c_str()))
		return std::string(contents);
	else
		return "";
}

TEST_CASE( "Correct entity ids are returned" ) {
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

	auto api_client = rest_api_client(web::uri("https://discordapp.com/api/v6"), token, disccord::token_type::Bot);
	auto route = disccord::rest::Route("GET", "/users/@me");

	api_client.request<user>(route).then([=](user ent){
		CAPTURE(ent.get_id());
		REQUIRE(ent.get_id() == id);
	}).wait();
}