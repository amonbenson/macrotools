// #define LOG_PRINTF demo_printf

#include "macrotools/test.h"
#include "macrotools/log.h"

DESCRIBE(test_log, "log") {
    IT("prints errors") {
        LOG_ERROR("Some message.");
    }
}
