// mock the printf function
#define mock_printf(format, ...) snprintf(mock_stdout, sizeof(mock_stdout), format, __VA_ARGS__);

#define LOG_PRINTF mock_printf
#define LOG_GLOBAL_LEVEL LOG_LEVEL_WARN

#include <string.h>
#include "macrotools/test.h"
#include "macrotools/log.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

char mock_stdout[1024];

DESCRIBE(test_log, "log") {
    IT("logs messages") {
        int log_line;

        snprintf(mock_stdout, sizeof(mock_stdout), "123");
        // clang-format off
        LOG_ERROR("Some message."); log_line = __LINE__;
        // clang-format on

        char expected_stdout[1024];
        snprintf(expected_stdout, sizeof(expected_stdout),
            MT_BACKGROUND_RED " ERROR " MT_COLOR_RESET " %s:%d: Some message.\r\n",
            __FILE__,
            log_line);
        EXPECT_STRING_EQ(mock_stdout, expected_stdout, MIN(sizeof(mock_stdout), sizeof(expected_stdout)));
    }

    IT("skips logging if the level is not enabled") {
        snprintf(mock_stdout, sizeof(mock_stdout), "123");
        LOG_TRACE("Some other message.");

        EXPECT_STRING_EQ(mock_stdout, "123", sizeof(mock_stdout));
    }
}
