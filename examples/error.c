#include <stdio.h>
#include "macrotools/error.h"

int good_function() { return 0; }

int bad_function() { return 1; }

int main(int argc, const char *argv[]) {
    TRY_OR_RETURN(good_function(), "good_function() failed.");
    TRY_OR_RETURN(TRY_ASSERT(0 == 0), "Assertion failed: 0 == 0. The universe is broken.");
    TRY_OR_WARN(bad_function(), "bad_function() failed. Continuing...");
    TRY_OR_RETURN(bad_function(), "bad_function() failed again! Who could have known?");

    return 0; // never reached
}
