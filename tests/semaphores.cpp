#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <util/semaphore.hpp>

using namespace disccord::util;

SCENARIO("semaphores can be entered") {
	GIVEN("a semaphore with limit 1") {
		semaphore mySemaphore(1);

		REQUIRE(mySemaphore.get_current_count() == 1);

		WHEN("we enter the semaphore") {
			bool result = mySemaphore.enter().get();

			CHECK(result == true);

			THEN("the current count decreases") {
				REQUIRE(mySemaphore.get_current_count() == 0);
			}
		}
		AND_WHEN("we release the semaphore") {
			mySemaphore.release();

			THEN("the current count increases") {
				REQUIRE(mySemaphore.get_current_count() == 1);
			}
		}
	}
}