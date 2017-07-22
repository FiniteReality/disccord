#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <disccord/rest/route.hpp>

using namespace disccord::rest;

SCENARIO("correct route info is returned") {
    WHEN("we provide no parameters") {
        auto myRoute = build_route<0>("GET", "/gateway", {});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/gateway");
        REQUIRE(myRoute.bucket_url == "/gateway");
    }

    WHEN("we provide no parameters but a different method") {
        auto myRoute = build_route<0>("POST", "/gateway", {});

        REQUIRE(myRoute.method == "POST");
        REQUIRE(myRoute.full_url == "/gateway");
        REQUIRE(myRoute.bucket_url == "/gateway");
    }

    WHEN("we provide a single major parameter") {
        auto myRoute = build_route<1>(
            "GET", "/guilds/{guild.id}", {"1234567890"});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/guilds/1234567890");
        REQUIRE(myRoute.bucket_url == "/guilds/1234567890");
    }

    WHEN("we provide multiple major parameters") {
        auto myRoute = build_route<2>(
            "GET", "/guilds/{guild.id}/channels/{channel.id}",
            {"1234567890", "0987654321"});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == 
            "/guilds/1234567890/channels/0987654321");
        REQUIRE(myRoute.bucket_url ==
            "/guilds/1234567890/channels/0987654321");
    }

    WHEN("we provide a single major parameter and a minor parameter") {
        auto myRoute = build_route<2>(
            "GET", "/guilds/{guild.id}/emojis/{emoji.id}",
            {"1234567890", "0987654321"});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/guilds/1234567890/emojis/0987654321");
        REQUIRE(myRoute.bucket_url == "/guilds/1234567890/emojis/{emoji.id}");
    }

    WHEN("we provide a single major parameter and multiple minor parameters") {
        auto myRoute = build_route<4>(
            "DELETE", "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}",
            {"1234567890", "0987654321", "1234567890", "0987654321"});

        REQUIRE(myRoute.method == "DELETE");
        REQUIRE(myRoute.full_url == "/channels/1234567890/messages/0987654321/reactions/1234567890/0987654321");
        REQUIRE(myRoute.bucket_url == "/channels/1234567890/messages/{message.id}/reactions/{emoji}/{user.id}");
    }

    WHEN("we provide a single minor parameter") {
        auto myRoute = build_route<1>(
            "GET", "/emojis/{emoji.id}", {"1234567890"});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/emojis/1234567890");
        REQUIRE(myRoute.bucket_url == "/emojis/{emoji.id}");
    }

    WHEN("we provide multiple minor parameters") {
        auto myRoute = build_route<2>(
            "GET", "/roles/{role.id}/emojis/{emoji.id}",
            {"1234567890", "0987654321"});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/roles/1234567890/emojis/0987654321");
        REQUIRE(myRoute.bucket_url == "/roles/{role.id}/emojis/{emoji.id}");
    }

    WHEN("we provide a minor followed by a major parameter") {
        auto myRoute = build_route<2>(
            "GET", "/emojis/{emoji.id}/guilds/{guild.id}",
            {"0123456789", "0987654321"});

        REQUIRE(myRoute.method == "GET");
        REQUIRE(myRoute.full_url == "/emojis/0123456789/guilds/0987654321");
        REQUIRE(myRoute.bucket_url == "/emojis/{emoji.id}/guilds/0987654321");
    }
}
