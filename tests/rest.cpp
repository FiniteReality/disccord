#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <rest/api_client.hpp>
#include <rest/route.hpp>

#include <iostream>
#include <fstream>

#include <execinfo.h>

using namespace disccord::rest::internal;

TEST_CASE( "Correct entity ids are returned" ) {
	std::string token;

	std::ifstream file("test_data/token.data.txt");
	std::getline(file, token);

	REQUIRE(!token.empty());

	auto api_client = rest_api_client(web::uri("https://discordapp.com/api/v6"), token, disccord::token_type::Bot);
	auto route = disccord::rest::Route("GET", "/users/@me");

	api_client.request(route).then([](pplx::task<disccord::models::entity<uint64_t>> entity_task){
		auto entity = entity_task.get();
		std::cout << "Got entity ID: " << entity.getId() << std::endl;
		REQUIRE(entity.getId() == 257584807716978688);
	}).wait();
}