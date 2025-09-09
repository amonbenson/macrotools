#include "macrotools/test/node.h"
#include "macrotools/log.h"
#include <stddef.h>


void mt_test_node_init(mt_test_node_t *node, int type, const char *name) {
    node->type = type;
    node->name = name;
    node->level = 0;
    node->num_children = 0;
    node->parent = NULL;
    node->first_child = NULL;
    node->last_child = NULL;
    node->next_sibling = NULL;
}

void mt_test_node_update_level(mt_test_node_t *node, int level) {
    node->level = level;

    // update each child recursively
    mt_test_node_t *child = node->first_child;
    while (child != NULL) {
        mt_test_node_update_level(child, level + 1);
        child = child->next_sibling;
    }
}

void mt_test_node_add_child(mt_test_node_t *parent, mt_test_node_t *child) {
    if (child->parent || child->next_sibling) {
        LOG_ERROR("Cannot add child: child \"%s\" is already part of another node tree.", child->name);
        return;
    }

    // update the parent's children list
    if (!parent->first_child) {
        parent->first_child = child;
    }
    if (parent->last_child) {
        parent->last_child->next_sibling = child;
    }
    parent->last_child = child;
    child->next_sibling = NULL;
    parent->num_children++;

    // update the child's parent
    child->parent = parent;

    // update the child's level
    mt_test_node_update_level(child, parent->level + 1);
}

void mt_test_node_debug_print(mt_test_node_t *node, int recurse) {
    // print node type and name
    for (int i = 0; i < node->level; i++) {
        printf("  ");
    }
    printf("- %s \"%s\"", __MT_TEST_NODE_TYPE_STR(node->type), node->name);

    // print type-specific infos
    switch (node->type) {
        case __MT_TEST_NODE_CASE:
            const mt_test_case_t *tcase = (mt_test_case_t *) node;
            printf(" suite=\"%s\"", tcase->suite ? tcase->suite->node.name : "???");
            break;
        default:
            break;
    }

    printf("\r\n");

    // print children recursively
    if (recurse) {
        mt_test_node_t *child = node->first_child;
        while (child) {
            mt_test_node_debug_print(child, recurse);
            child = child->next_sibling;
        }
    }
}

void mt_test_plan_init(mt_test_plan_t *plan, const char *name) {
    mt_test_node_init(&plan->node, __MT_TEST_NODE_PLAN, name);
    plan->num_suites_failed = 0;
    plan->num_cases_failed = 0;
}

void mt_test_suite_init(mt_test_suite_t *suite, mt_test_plan_t *plan, const char *name) {
    mt_test_node_init(&suite->node, __MT_TEST_NODE_SUITE, name);
    mt_test_node_add_child(&plan->node, &suite->node);
}

void mt_test_case_init(mt_test_case_t *tcase, mt_test_node_t *parent, const char *name) {
    // use suite as the default parent
    mt_test_node_init(&tcase->node, __MT_TEST_NODE_CASE, name);
    tcase->suite = __MT_TEST_NODE_GET_SUITE(parent);
    if (tcase->suite == NULL) {
        LOG_ERROR("Test case parent was neither a test suite nor another test case.");
        return;
    }

    mt_test_node_add_child(parent, &tcase->node);
}
