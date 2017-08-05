#include "catch.hpp"

#include <disccord/util/url_encode.hpp>

using namespace disccord::util;

SCENARIO("url encoding emoji-related strings") {
	GIVEN("a codepoint string") {
		WHEN("we have White Heavy Check Mark") {
            
			std::string url_encoded_str = "%E2%9C%85";
            auto result = url_encode("\U00002705");
            
			THEN("the string has been encoded") {
				REQUIRE(result == url_encoded_str);
			}
		}
        AND_WHEN("we have Thinking Face") {
            
			std::string url_encoded_str = "%F0%9F%A4%94";
            auto result = url_encode("\U0001F914");
            
			THEN("the string has been encoded") {
				REQUIRE(result == url_encoded_str);
			}
		}
	}
    GIVEN("an emoji string") {
        WHEN("we have a White Heavy Check Mark") {
            
			std::string url_encoded_str = "%E2%9C%85";
            auto result = url_encode("✅");
            
			THEN("the string has been encoded") {
				REQUIRE(result == url_encoded_str);
			}
		}
        AND_WHEN("we have Thinking Face") {
            
			std::string url_encoded_str = "%F0%9F%A4%94";
            auto result = url_encode("🤔");
            
			THEN("the string has been encoded") {
				REQUIRE(result == url_encoded_str);
			}
		}
    }
    GIVEN("a custom emoji string") {
        WHEN("we have :blobthinking: from Google Emoji") {
            
			std::string url_encoded_str = "blobthinking%3A280622559458885633";
            auto result = url_encode("blobthinking:280622559458885633");
            
			THEN("the string has been encoded") {
				REQUIRE(result == url_encoded_str);
			}
		}
    }
}
