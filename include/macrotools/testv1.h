#pragma once

#include "macrotools/color.h"
#include <ctype.h>
#include <string.h>
#include <stddef.h>


#ifndef TEST_PRINTF
    #include <stdio.h>
    #define TEST_PRINTF printf
#endif

#ifndef TEST_STRINGS
    #define TEST_STRINGS 1
#endif


#define __TEST_ABS(a) (((a) < 0) ? (-(a)) : (a))

#define __TEST_STRINGIFY_IMPL(x) #x
#define __TEST_STRINGIFY(x) __TEST_STRINGIFY_IMPL(x)

#define __TEST_PRINT_CHAR(c) (isprint(c) ? TEST_PRINTF("%c", (c)) : TEST_PRINTF("\\x%02x", (c)))


typedef struct {
    int num_total;
    int num_failed;
} test_suite_t;

typedef test_suite_t (*test_suite_run_t)(void);


#define __TEST_MARK_FAILED() do { \
    __current_test_failed = 1; \
    __test_suite->num_failed++; \
    TEST_PRINTF(MT_COLOR_RED "\r\n => Assertion failed at %s:%d" MT_COLOR_RESET "\r\n", __FILE__, __LINE__); \
} while (0)

#define FAIL() { \
    __TEST_MARK_FAILED(); \
    TEST_PRINTF("\r\n"); \
    continue; \
}

#define __TEST_ASSERTION(actual_type, actual_expr, expected_type, expected_expr, pass_expr, ...) { \
    actual_type _actual_value = (actual_type) (actual_expr); \
    expected_type _expected_value = (expected_type) (expected_expr); \
    (void) _expected_value; \
    if (!(pass_expr)) { \
        __TEST_MARK_FAILED(); \
        __VA_ARGS__; \
        continue; \
    } \
}

#define __TEST_ASSERTION_SIMPLE(actual_type, actual_expr, expected_type, expected_expr, pass_expr, print_expr) \
    __TEST_ASSERTION(actual_type, actual_expr, expected_type, expected_expr, pass_expr, { \
        TEST_PRINTF(MT_COLOR_RED "    Expected "); \
        print_expr; \
        TEST_PRINTF(MT_COLOR_RESET "\r\n\r\n"); \
    });

#define __TEST_ASSERTION_DIFF(actual_type, actual_expr, expected_type, expected_expr, pass_expr, actual_print_expr, expected_print_expr) \
    __TEST_ASSERTION(actual_type, actual_expr, expected_type, expected_expr, pass_expr, { \
        TEST_PRINTF("\r\n" MT_COLOR_GREEN "  - Expected: "); \
        expected_print_expr; \
        TEST_PRINTF(MT_COLOR_RESET "\r\n" MT_COLOR_RED "  + Received: "); \
        actual_print_expr; \
        TEST_PRINTF(MT_COLOR_RESET "\r\n\r\n"); \
    });

#define __TEST_ASSERTION_STRINGIFY(actual_type, actual_expr, expected_type, expected_expr, pass_expr, expector_fmt) \
    __TEST_ASSERTION_SIMPLE(actual_type, actual_expr, expected_type, expected_expr, pass_expr, { \
        TEST_PRINTF(expector_fmt, __TEST_STRINGIFY(actual_expr), __TEST_STRINGIFY(expected_expr)); \
    });


// generic comparators
#define EXPECT(actual) __TEST_ASSERTION_STRINGIFY(typeof(actual), actual, int, -1, _actual_value, "'%s'%.0s")

// boolean comparators
#define EXPECT_TRUE(actual) __TEST_ASSERTION_DIFF(int, actual, int, -1, _actual_value, { \
        TEST_PRINTF("%d (false)", _actual_value); \
    }, { \
        TEST_PRINTF("1 (true)"); \
    });
#define EXPECT_FALSE(actual) __TEST_ASSERTION_DIFF(int, actual, int, -1, !_actual_value, { \
        TEST_PRINTF("%d (true)", _actual_value); \
    }, { \
        TEST_PRINTF("0 (false)"); \
    });

// integral comparators
#define __EXPECT_INTEGRAL(actual, expected, type, type_fmt, comparator, comparator_fmt) \
    __TEST_ASSERTION_SIMPLE(type, actual, type, expected, _actual_value comparator _expected_value, TEST_PRINTF(type_fmt " " comparator_fmt " " type_fmt, _actual_value, _expected_value));

#define __EXPECT_INTEGRAL_CLOSE_TO(actual, expected, delta, type, type_fmt) { \
    typeof(type) _delta_value = (type) delta; \
    __TEST_ASSERTION_SIMPLE(type, actual, type, expected, __TEST_ABS(_actual_value - _expected_value) <= _delta_value, \
        TEST_PRINTF(type_fmt " to be close to " type_fmt " (received difference " type_fmt ", but expected at most " type_fmt ")", _actual_value, _expected_value, __TEST_ABS(_actual_value - _expected_value), _delta_value)); \
}

#define __EXPECT_INTEGRAL_NOT_CLOSE_TO(actual, expected, delta, type, type_fmt) { \
    typeof(type) _delta_value = (type) delta; \
    __TEST_ASSERTION_SIMPLE(type, actual, type, expected, __TEST_ABS(_actual_value - _expected_value) > _delta_value, \
        TEST_PRINTF(type_fmt " to be close to " type_fmt " (received difference " type_fmt ", but expected more than " type_fmt ")", _actual_value, _expected_value, __TEST_ABS(_actual_value - _expected_value), _delta_value)); \
}

#define EXPECT_POINTER_EQ(actual, expected) __EXPECT_INTEGRAL(actual, expected, void *, "%p", ==, "to equal")
#define EXPECT_POINTER_NE(actual, expected) __EXPECT_INTEGRAL(actual, expected, void *, "%p", !=, "to not equal")

#define EXPECT_SIGNED_GT(actual, expected) __EXPECT_INTEGRAL(actual, expected, long long int, "%lld", >, "to be greater than")
#define EXPECT_SIGNED_GE(actual, expected) __EXPECT_INTEGRAL(actual, expected, long long int, "%lld", >=, "to be greater than or equal to")
#define EXPECT_SIGNED_LT(actual, expected) __EXPECT_INTEGRAL(actual, expected, long long int, "%lld", <, "to be less than")
#define EXPECT_SIGNED_LE(actual, expected) __EXPECT_INTEGRAL(actual, expected, long long int, "%lld", <=, "to be less than or equal to")
#define EXPECT_SIGNED_CLOSE_TO(actual, expected, delta) __EXPECT_INTEGRAL_CLOSE_TO(actual, expected, delta, long long int, "%lld")
#define EXPECT_SIGNED_NOT_CLOSE_TO(actual, expected, delta) __EXPECT_INTEGRAL_NOT_CLOSE_TO(actual, expected, delta, long long int, "%lld")

#define EXPECT_EQ(actual, expected) __EXPECT_INTEGRAL(actual, expected, unsigned long long int, "%llu", ==, "to equal")
#define EXPECT_NE(actual, expected) __EXPECT_INTEGRAL(actual, expected, unsigned long long int, "%llu", !=, "to not equal")
#define EXPECT_UNSIGNED_GT(actual, expected) __EXPECT_INTEGRAL(actual, expected, unsigned long long int, "%llu", >, "to be greater than")
#define EXPECT_UNSIGNED_GE(actual, expected) __EXPECT_INTEGRAL(actual, expected, unsigned long long int, "%llu", >=, "to be greater than or equal to")
#define EXPECT_UNSIGNED_LT(actual, expected) __EXPECT_INTEGRAL(actual, expected, unsigned long long int, "%llu", <, "to be less than")
#define EXPECT_UNSIGNED_LE(actual, expected) __EXPECT_INTEGRAL(actual, expected, unsigned long long int, "%llu", <=, "to be less than or equal to")
#define EXPECT_UNSIGNED_CLOSE_TO(actual, expected, delta) __EXPECT_INTEGRAL_CLOSE_TO(actual, expected, delta, unsigned long long int, "%llu")
#define EXPECT_UNSIGNED_NOT_CLOSE_TO(actual, expected, delta) __EXPECT_INTEGRAL_NOT_CLOSE_TO(actual, expected, delta, unsigned long long int, "%llu")

#define EXPECT_FLOATING_GT(actual, expected) __EXPECT_INTEGRAL(actual, expected, long double, "%Lf", >, "to be greater than")
#define EXPECT_FLOATING_GE(actual, expected, delta) __EXPECT_INTEGRAL(actual + delta, expected, long double, "%Lf", >, "to be greater than or close to")
#define EXPECT_FLOATING_LT(actual, expected) __EXPECT_INTEGRAL(actual, expected, long double, "%Lf", <, "to be less than")
#define EXPECT_FLOATING_LE(actual, expected, delta) __EXPECT_INTEGRAL(actual - delta, expected, long double, "%Lf", <, "to be less than or close to")
#define EXPECT_FLOATING_CLOSE_TO(actual, expected, delta) __EXPECT_INTEGRAL_CLOSE_TO(actual, expected, delta, long double, "%Lf")
#define EXPECT_FLOATING_NOT_CLOSE_TO(actual, expected, delta) __EXPECT_INTEGRAL_NOT_CLOSE_TO(actual, expected, delta, long double, "%Lf")

// string comparators
#define EXPECT_STRING_EQ(actual, expected, n) { \
    size_t _n = (size_t) (n); \
    __TEST_ASSERTION_DIFF(const char *, actual, const char *, expected, strncmp(_actual_value, _expected_value, _n) == 0, { \
        for (size_t i = 0; i < _n && _actual_value[i] != '\0'; i++) { __TEST_PRINT_CHAR(_actual_value[i]); } \
    }, { \
        for (size_t i = 0; i < _n && _expected_value[i] != '\0'; i++) { __TEST_PRINT_CHAR(_expected_value[i]); } \
    }); \
}

#define EXPECT_STRING_NOT_EQ(actual, expected, n) { \
    size_t _n = (size_t) (n); \
    __TEST_ASSERTION_SIMPLE(const char *, actual, const char *, expected, strncmp(_actual_value, _expected_value, _n) != 0, { \
        TEST_PRINTF("any string other than \""); \
        for (size_t i = 0; i < _n && _actual_value[i] != '\0'; i++) { __TEST_PRINT_CHAR(_actual_value[i]); }; \
        TEST_PRINTF("\""); \
    }); \
}

#define EXPECT_BUFFER_EQ(actual, expected, n) { \
    size_t _n = (size_t) (n); \
    __TEST_ASSERTION_DIFF(const unsigned char *, actual, const unsigned char *, expected, memcmp(_actual_value, _expected_value, _n) == 0, { \
        TEST_PRINTF("hex "); for (size_t i = 0; i < _n; i++) { TEST_PRINTF("%02x ", _actual_value[i]); } \
    }, { \
        TEST_PRINTF("hex "); for (size_t i = 0; i < _n; i++) { TEST_PRINTF("%02x ", _expected_value[i]); } \
    }); \
}

#define EXPECT_BUFFER_NOT_EQ(actual, expected, n) { \
    size_t _n = (size_t) (n); \
    __TEST_ASSERTION_SIMPLE(const char *, actual, const char *, expected, memcmp(_actual_value, _expected_value, _n) != 0, { \
        TEST_PRINTF("any buffer other than hex: "); \
        for (size_t i = 0; i < _n; i++) { TEST_PRINTF("%02x ", _actual_value[i]); }; \
    }); \
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


#define IT(name) __TEST_DECLARE_TEST(name)
#define TEST(name) __TEST_DECLARE_TEST(name)

#define DESCRIBE(label, name) __TEST_DECLARE_TEST_SUITE(label, name)
#define TEST_SUITE(label, name) __TEST_DECLARE_TEST_SUITE(label, name)


#define TEST_MAIN(...) int main(int argc, const char *argv[]) { \
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

#define TEST_MAIN_EXTERN(...) \
    extern test_suite_run_t __VA_ARGS__; \
    TEST_MAIN(__VA_ARGS__)
