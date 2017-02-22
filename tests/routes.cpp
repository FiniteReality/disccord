#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <rest/route.hpp>

using namespace disccord::rest;

SCENARIO("correct route info is returned") {
    WHEN("we provide no parameters") {
        auto myRoute = get_route("GET", "/gateway");

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/gateway");
        REQUIRE(myRoute.bucket_url == "/gateway");
    }

    WHEN("we provide no parameters but a different method") {
        auto myRoute = get_route("POST", "/gateway");

        REQUIRE(myRoute.method == "POST");
        REQUIRE(myRoute.full_url == "/gateway");
        REQUIRE(myRoute.bucket_url == "/gateway");
    }

    WHEN("we provide a single major parameter") {
        auto myRoute = get_route("GET", "/guilds/{guild.id}", "1234567890");

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/guilds/1234567890");
        REQUIRE(myRoute.bucket_url == "/guilds/1234567890");
    }

    WHEN("we provide multiple major parameters") {
        auto myRoute = get_route("GET",
            "/guilds/{guild.id}/channels/{channel.id}",
            "1234567890", "0987654321");

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/guilds/1234567890/channels/0987654321");
        REQUIRE(myRoute.bucket_url ==
            "/guilds/1234567890/channels/0987654321");
    }

    WHEN("we provide a single major parameter and a minor parameter") {
        auto myRoute = get_route("GET", "/guilds/{guild.id}/emojis/{emoji.id}",
            "1234567890", "0987654321");

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/guilds/1234567890/emojis/0987654321");
        REQUIRE(myRoute.bucket_url == "/guilds/1234567890/emojis/{emoji.id}");
    }

    WHEN("we provide a single minor parameter") {
        auto myRoute = get_route("GET", "/emojis/{emoji.id}", "1234567890");

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/emojis/1234567890");
        REQUIRE(myRoute.bucket_url == "/emojis/{emoji.id}");
    }

    WHEN("we provide multiple minor parameters") {
        auto myRoute = get_route("GET", "/roles/{role.id}/emojis/{emoji.id}",
            "1234567890", "0987654321");

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/roles/1234567890/emojis/0987654321");
        REQUIRE(myRoute.bucket_url == "/roles/{role.id}/emojis/{emoji.id}");
    }
}