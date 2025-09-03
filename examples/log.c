#define LOG_GLOBAL_LEVEL LOG_LEVEL_DEBUG

#include "macrotools/log.h"

int main(int argc, const char *argv[]) {
    LOG_TRACE("The global level is DEBUG, so this should not get printed.");
    LOG_DEBUG("You see this?");
    LOG_INFO("It's just for your own information ...");
    LOG_WARN("This is not good.");
    LOG_ERROR("We got a serious problem!");

    return 0;
}
