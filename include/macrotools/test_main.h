#include "macrotools/test.h"
#include "macrotools/test/node_impl.h"


#define TEST_MAIN(...) \
    int main(int argc, const char *argv[]) { \
        static mt_test_plan_t plan; \
        mt_test_plan_init(&plan, "root_plan"); \
        \
        const test_suite_wrapper_t suite_wrappers[] = { __VA_ARGS__ }; \
        for (int i = 0; i < sizeof(suite_wrappers) / sizeof(suite_wrappers[0]); i++) { \
            suite_wrappers[i](&plan); \
        } \
        \
        mt_test_node_debug_print(&plan.node, 1); \
        \
        return 0; \
    }

#define TEST_MAIN_EXTERN(...) \
    extern test_suite_wrapper_t __VA_ARGS__; \
    TEST_MAIN(__VA_ARGS__)
