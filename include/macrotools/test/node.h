#pragma once

#define __MT_TEST_NODE_UNKNOWN 0
#define __MT_TEST_NODE_PLAN 1
#define __MT_TEST_NODE_SUITE 2
#define __MT_TEST_NODE_CASE 3
#define __MT_TEST_NODE_EXPECT 4

#define __MT_TEST_NODE_TYPE_STR(x) \
    ((x) == __MT_TEST_NODE_PLAN ? "plan" : \
    ((x) == __MT_TEST_NODE_SUITE ? "suite" : \
    ((x) == __MT_TEST_NODE_CASE ? "case" : \
    ((x) == __MT_TEST_NODE_EXPECT ? "expect" : "unknown"))))


typedef struct mt_test_node mt_test_node_t;
typedef struct mt_test_plan mt_test_plan_t;
typedef struct mt_test_suite mt_test_suite_t;
typedef struct mt_test_case mt_test_case_t;


struct mt_test_node {
    int type;
    const char *name;
    int level;
    int num_children;
    struct mt_test_node *parent;
    struct mt_test_node *first_child;
    struct mt_test_node *last_child;
    struct mt_test_node *next_sibling;
};

struct mt_test_plan {
    struct mt_test_node node;
    int num_suites_failed;
    int num_cases_failed;
};

struct mt_test_suite {
    struct mt_test_node node;
    int failed;
};

struct mt_test_case {
    struct mt_test_node node;
    mt_test_suite_t *suite;
    int failed;
};

#define __MT_TEST_NODE_GET_SUITE(node) \
    ((node)->type == __MT_TEST_NODE_SUITE ? ((mt_test_suite_t *) (node)) : \
    ((node)->type == __MT_TEST_NODE_CASE ? (((mt_test_case_t *) (node))->suite) : \
    NULL))
#define __MT_TEST_NODE_GET_PLAN(node) ((mt_test_plan_t *) (__MT_TEST_NODE_SUITE(node)->parent))


void mt_test_node_init(mt_test_node_t *node, int type, const char *name);
void mt_test_node_update_level(mt_test_node_t *node, int level);
void mt_test_node_add_child(mt_test_node_t *parent, mt_test_node_t *child);
void mt_test_node_debug_print(mt_test_node_t *node, int recurse);

void mt_test_plan_init(mt_test_plan_t *plan, const char *name);
void mt_test_suite_init(mt_test_suite_t *suite, mt_test_plan_t *plan, const char *name);
void mt_test_case_init(mt_test_case_t *tcase, mt_test_node_t *parent, const char *name);
