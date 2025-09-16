#pragma once


typedef enum {
    MT_SCOPE_PHASE_SETUP = 0,
    MT_SCOPE_PHASE_RUN = 1,
    MT_SCOPE_PHASE_TEARDOWN = 2,
    MT_SCOPE_PHASE_EXIT = 3,
} mt_scope_phase_t;

typedef struct {
    int level;
    mt_scope_phase_t outer_phase;
    mt_scope_phase_t inner_phase;
    int tier;
    int i;
    int n;
} mt_scope_t;


#define MT_SCOPE_PHASE_STR(x) \
    ((x) == MT_SCOPE_PHASE_SETUP ? "setup" : \
    ((x) == MT_SCOPE_PHASE_RUN ? "run" : \
    ((x) == MT_SCOPE_PHASE_TEARDOWN ? "teardown" : \
    ((x) == MT_SCOPE_PHASE_EXIT ? "exit" : \
    "unknown"))))

#define MT_SCOPE_SHELL() for (int __mt_scope_shell = 1; __mt_scope_shell; __mt_scope_shell = 0)
#define MT_SCOPE_SHELL_DEFINE(expr) for (expr; __mt_scope_shell; __mt_scope_shell = 0)
#define MT_SCOPE_SHELL_BEFORE(expr) for (; __mt_scope_shell && ((expr), 1); __mt_scope_shell = 0)
#define MT_SCOPE_SHELL_AFTER(expr) for (; __mt_scope_shell; __mt_scope_shell = 0, (expr))
#define MT_SCOPE_IF(expr) if (expr)

#define MT_SCOPE_HOOK_BEFORE_ALL() \
    MT_SCOPE_SHELL() \
    MT_SCOPE_IF(__mt_scope->outer_phase == MT_SCOPE_PHASE_SETUP)

#define MT_SCOPE_HOOK_AFTER_ALL() \
    MT_SCOPE_SHELL() \
    MT_SCOPE_IF(__mt_scope->outer_phase == MT_SCOPE_PHASE_TEARDOWN)

#define MT_SCOPE_HOOK_BEFORE_EACH() \
    MT_SCOPE_SHELL() \
    MT_SCOPE_IF(__mt_scope->outer_phase == MT_SCOPE_PHASE_RUN && __mt_scope->inner_phase == MT_SCOPE_PHASE_SETUP)

#define MT_SCOPE_HOOK_AFTER_EACH() \
    MT_SCOPE_SHELL() \
    MT_SCOPE_IF(__mt_scope->outer_phase == MT_SCOPE_PHASE_RUN && __mt_scope->inner_phase == MT_SCOPE_PHASE_TEARDOWN)

#define MT_SCOPE_RUNNER() \
    MT_SCOPE_SHELL() \
    MT_SCOPE_SHELL_AFTER(__mt_scope->tier++) \
    MT_SCOPE_SHELL_BEFORE(__mt_scope->outer_phase == MT_SCOPE_PHASE_SETUP ? __mt_scope->n++ : 0) \
    MT_SCOPE_IF(__mt_scope->outer_phase == MT_SCOPE_PHASE_RUN && __mt_scope->inner_phase == MT_SCOPE_PHASE_RUN && __mt_scope->tier == __mt_scope->i)

#define __MT_SCOPE_FROM_PARENT(parent_scope) ((mt_scope_t) { \
    .level = (parent_scope)->level + 1, \
    .outer_phase = MT_SCOPE_PHASE_SETUP, \
    .inner_phase = MT_SCOPE_PHASE_SETUP, \
    .tier = 0, \
    .i = 0, \
    .n = 0,\
})

#define MT_SCOPE() \
    MT_SCOPE_RUNNER() \
    MT_SCOPE_SHELL_DEFINE(mt_scope_t *__mt_parent_scope = __mt_scope) \
    MT_SCOPE_SHELL_DEFINE(mt_scope_t __mt_scope_obj = __MT_SCOPE_FROM_PARENT(__mt_parent_scope)) \
    MT_SCOPE_SHELL_DEFINE(mt_scope_t *__mt_scope = &__mt_scope_obj) \
    for ( \
        __mt_scope->outer_phase = MT_SCOPE_PHASE_SETUP; \
        __mt_scope->outer_phase != MT_SCOPE_PHASE_EXIT; \
        __mt_scope->outer_phase++ \
    ) \
    for ( \
        __mt_scope->i = 0; \
        __mt_scope->i < (__mt_scope->outer_phase == MT_SCOPE_PHASE_RUN ? __mt_scope->n : 1); \
        __mt_scope->i++ \
    ) \
    for ( \
        __mt_scope->inner_phase = MT_SCOPE_PHASE_SETUP, __mt_scope->tier = 0; \
        __mt_scope->outer_phase == MT_SCOPE_PHASE_RUN \
            ? __mt_scope->inner_phase != MT_SCOPE_PHASE_EXIT \
            : __mt_scope->inner_phase == MT_SCOPE_PHASE_SETUP; \
        __mt_scope->inner_phase++, __mt_scope->tier = 0 \
    ) \
    MT_SCOPE_SHELL()

#define MT_SCOPE_DEBUG_PRINT() printf("scope level %d, tier %d, outer phase \"%s\", inner phase \"%s\", iteration %d/%d\r\n", \
    __mt_scope->level, __mt_scope->tier, MT_SCOPE_PHASE_STR(__mt_scope->outer_phase), MT_SCOPE_PHASE_STR(__mt_scope->inner_phase), __mt_scope->i, __mt_scope->n);

#define MT_SCOPE_DEFINE_ROOT() mt_scope_t __mt_scope_obj = { \
    .level = 0, \
    .outer_phase = MT_SCOPE_PHASE_RUN, \
    .inner_phase = MT_SCOPE_PHASE_RUN, \
    .tier = 0, \
    .i = 0, \
    .n = 1, \
}; mt_scope_t *__mt_scope = &__mt_scope_obj;
