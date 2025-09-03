#include <string.h>
#include "macrotools/test.h"

DESCRIBE(suite_one, "basic assertions") {
    IT("compares numbers") {
        EXPECT_EQ(1, 1);
        EXPECT_NE(1, 2);
        EXPECT(123 == 123);
    }
}

int always_twenty() {
    return 20;
}

DESCRIBE(suite_two, "advanced examples") {
    // you can declare local variables here. Note that they DO NOT get reset after each test run.
    const char *blub_str = "blub";

    IT("checks function return values") {
        EXPECT_EQ(always_twenty(), 20);
    }

    IT("checks strings (using strcmp)") {
        EXPECT_EQ(strcmp(blub_str, "blub"), 0);
    }
}

// List all your test suites here.
// Use TEST_MAIN_EXTERN(...) if you want to link test suites from separate c files.
TEST_MAIN(suite_one, suite_two)
