#pragma once

#include "macrotools/color.h"

#ifndef TEST_PRINTF
    #include <stdio.h>
    #define TEST_PRINTF printf
#endif


#define __TEST_STRINGIFY_IMPL(x) #x
#define __TEST_STRINGIFY(x) __TEST_STRINGIFY_IMPL(x)


typedef struct {
    int num_total;
    int num_failed;
} test_suite_t;

typedef test_suite_t (*test_suite_run_t)(void);


#define FAIL() {\
    __current_test_failed = 1; \
    __test_suite->num_failed++; \
    TEST_PRINTF("" MT_COLOR_RED " => Assertion failed at %s:%d:"MT_COLOR_RESET"\r\n", __FILE__, __LINE__); \
    continue; \
}

#define EXPECT(expr) \
    if (!(expr)) { \
        TEST_PRINTF("" MT_COLOR_RED " => Expected '%s' to be true." MT_COLOR_RESET "\r\n", __TEST_STRINGIFY(expr)); \
        FAIL(); \
    }

#define EXPECT_EQ(a, b) \
    if ((a) != (b)) { \
        TEST_PRINTF("" MT_COLOR_RED " => Expected '%s' to equal '%s'." MT_COLOR_RESET "\r\n", __TEST_STRINGIFY(a), __TEST_STRINGIFY(b)); \
        FAIL(); \
    }

#define EXPECT_NE(a, b) \
    if ((a) == (b)) { \
        TEST_PRINTF("" MT_COLOR_RED " => Expected '%s' not to equal '%s'." MT_COLOR_RESET "\r\n", __TEST_STRINGIFY(a), __TEST_STRINGIFY(b)); \
        FAIL(); \
    }

#define __TEST_DECLARE_TEST(name) for( \
    int __loop_break = 0, __current_test_failed = 0; \
    !__loop_break; \
    __loop_break = 1, __test_suite->num_total++, TEST_PRINTF("  %s %s\r\n", \
        __current_test_failed ? (MT_COLOR_RED "✗" MT_COLOR_RESET) : (MT_COLOR_GREEN "✓" MT_COLOR_RESET), \
        (name)) \
)

#define __TEST_DECLARE_TEST_SUITE(label, name) \
    test_suite_t __##label##_wrapper(void); \
    void __##label##_impl(test_suite_t *__test_suite); \
    \
    const test_suite_run_t label = __##label##_wrapper; \
    \
    test_suite_t __##label##_wrapper(void) { \
        test_suite_t suite = { .num_total = 0, .num_failed = 0 }; \
        TEST_PRINTF("\r\n%s\r\n", (name)); \
        __##label##_impl(&suite); \
        return suite; \
    } \
    void __##label##_impl(test_suite_t *__test_suite)


#define TEST(name) __TEST_DECLARE_TEST(name)
#define IT(name) __TEST_DECLARE_TEST(name)
#define DESCRIBE(label, name) __TEST_DECLARE_TEST_SUITE(label, name)


#define TEST_MAIN(...) \
    extern test_suite_run_t __VA_ARGS__; \
int main(int argc, const char *argv[]) { \
    const test_suite_run_t test_suites[] = { __VA_ARGS__ }; \
    \
    int suites_total = 0; \
    int suites_failed = 0; \
    int tests_total = 0; \
    int tests_failed = 0; \
    \
    for (int i = 0; i < sizeof(test_suites) / sizeof(test_suite_run_t); i++) { \
        const test_suite_t result = test_suites[i](); \
        suites_total++; \
        suites_failed += result.num_failed > 0 ? 1 : 0; \
        tests_total += result.num_total; \
        tests_failed += result.num_failed; \
    } \
    TEST_PRINTF("\r\n"); \
    if (suites_failed == 0) { \
        TEST_PRINTF(MT_BACKGROUND_GREEN " PASSED " MT_COLOR_RESET "\r\n"); \
        TEST_PRINTF("Test Suites: " MT_COLOR_GREEN "%d passed" MT_COLOR_RESET ", %d total.\r\n", suites_total - suites_failed, suites_total); \
        TEST_PRINTF("Tests:       " MT_COLOR_GREEN "%d passed" MT_COLOR_RESET ", %d total.\r\n", tests_total - tests_failed, tests_total); \
        return 0; \
    } else { \
        TEST_PRINTF(MT_BACKGROUND_RED " FAILED " MT_COLOR_RESET "\r\n"); \
        TEST_PRINTF("Test Suites: %d passed, " MT_COLOR_RED "%d failed" MT_COLOR_RESET ", %d total.\r\n", suites_total - suites_failed, suites_failed, suites_total); \
        TEST_PRINTF("Tests:       %d passed, " MT_COLOR_RED "%d failed" MT_COLOR_RESET ", %d total.\r\n", tests_total - tests_failed, tests_failed, tests_total); \
        return 1; \
    } \
}
