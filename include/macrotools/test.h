#pragma once

#include "macrotools/test/node.h"
#include "macrotools/utils.h"
#include "macrotools/scope.h"


typedef void (*test_suite_wrapper_t)(mt_test_plan_t *plan);


#define __MT_TEST_NODE_SCOPE(type, init_fn, ...) \
    static type MT_LINE_LABEL(__static_node); \
    MT_SCOPE() \
    MT_SCOPE_DEFINE(type *__new_context = &MT_LINE_LABEL(__static_node)) \
    MT_SCOPE_BEFORE(init_fn(__new_context, __context, ## __VA_ARGS__)) \
    MT_SCOPE_BEFORE(__context = &__new_context->node) \
    MT_SCOPE_AFTER(__context = __context->parent)

#define __MT_TEST_SUITE_WRAPPER(label, name) \
    void MT_CONCAT(label, _wrapper)(mt_test_plan_t *plan); \
    void MT_CONCAT(label, _impl)(mt_test_node_t *__context); \
    \
    const volatile test_suite_wrapper_t label = MT_CONCAT(label, _wrapper); \
    \
    void MT_CONCAT(label, _wrapper)(mt_test_plan_t *plan) { \
        static mt_test_suite_t suite; \
        mt_test_suite_init(&suite, plan, name); \
        MT_CONCAT(label, _impl)(&suite.node); \
    } \
    void MT_CONCAT(label, _impl)(mt_test_node_t *__context)

#define __MT_TEST_CASE_SCOPE(name) __MT_TEST_NODE_SCOPE(mt_test_case_t, mt_test_case_init, name)


#define TEST_SUITE(label, name) __MT_TEST_SUITE_WRAPPER(label, name)
#define DESCRIBE(label, name) __MT_TEST_SUITE_WRAPPER(label, name)

#define TEST(name) __MT_TEST_CASE_SCOPE(name)
#define IT(name) __MT_TEST_CASE_SCOPE(name)
