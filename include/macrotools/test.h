#pragma once

#include "macrotools/test/node.h"
#include "macrotools/utils.h"
#include "macrotools/scope.h"


typedef void (*test_suite_wrapper_t)(mt_scope_t *__mt_scope, mt_test_plan_t *__plan);


#define __MT_TEST_CURRENT_SOURCE() ((mt_test_source_t) { .file = __FILE__, .line = __LINE__ })

#define __MT_TEST_NODE_SCOPE(type, init_fn, ...) \
    static type MT_LINE_LABEL(__static_node); \
    MT_SCOPE() \
    MT_SCOPE_SHELL_DEFINE(type *__new_context = &MT_LINE_LABEL(__static_node)) \
    MT_SCOPE_SHELL_BEFORE(init_fn(__new_context, __context, ## __VA_ARGS__)) \
    MT_SCOPE_SHELL_BEFORE(__context = &__new_context->node) \
    MT_SCOPE_SHELL_AFTER(__context = __context->parent)

#define __MT_TEST_SUITE_WRAPPER(label, name) \
    void MT_CONCAT(label, _wrapper)(mt_test_plan_t *plan); \
    void MT_CONCAT(label, _impl)(mt_test_node_t *__context); \
    \
    const volatile test_suite_wrapper_t label = MT_CONCAT(label, _wrapper); \
    \
    void MT_CONCAT(label, _wrapper)(mt_scope_t *__mt_scope, mt_test_plan_t *plan) { \
        static mt_test_suite_t suite; \
        static mt_test_case_t root_case; \
        mt_test_suite_init(&suite, plan, name, __MT_TEST_CURRENT_SOURCE()); \
        mt_test_case_init(&root_case, &suite.node, name, __MT_TEST_CURRENT_SOURCE()); \
        MT_CONCAT(label, _impl)(&root_case.node); \
    } \
    void MT_CONCAT(label, _impl)(mt_test_node_t *__context)

#define __MT_TEST_CASE_SCOPE(name) __MT_TEST_NODE_SCOPE(mt_test_case_t, mt_test_case_init, name, __MT_TEST_CURRENT_SOURCE())


#define TEST_SUITE(label, name) __MT_TEST_SUITE_WRAPPER(label, name)
#define DESCRIBE(label, name) __MT_TEST_SUITE_WRAPPER(label, name)

#define TEST(name) __MT_TEST_CASE_SCOPE(name)
#define IT(name) __MT_TEST_CASE_SCOPE(name)
