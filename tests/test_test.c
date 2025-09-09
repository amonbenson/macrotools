#include "macrotools/test.h"
#include "macrotools/log.h"


DESCRIBE(test_test, "test") {
    IT("should do something") {
        LOG_INFO("Test running!");
    }
}
