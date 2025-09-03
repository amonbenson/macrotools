#include <stdio.h>
#include "macrotools/error.h"
#include "macrotools/log.h"

int good_function() { return 0; }

int bad_function() { return 1; }

int main(int argc, const char *argv[]) {
    // Note: The ret variable is only required when using TRY_OR_CLEANUP.
    // Make sure you initialize it to 0.
    int ret = 0;

    LOG_INFO("Allocating resources ...");

    TRY_OR_CLEANUP(good_function(), "good_function() failed.");
    TRY_OR_CLEANUP(bad_function(), "bad_function() failed.");

cleanup:
    LOG_INFO("Freeing resources. The return code is %d ...", ret);

    return ret;
}
