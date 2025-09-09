// no header guard, because these methods need to be defined for each compilation unit
// #pragma once


static volatile int __mt_enter_loop_flag;

#define MT_SCOPE() for (__mt_enter_loop_flag = 1; __mt_enter_loop_flag; __mt_enter_loop_flag = 0)

#define MT_SCOPE_DEFINE(expr) for (expr; __mt_enter_loop_flag; __mt_enter_loop_flag = 0)
#define MT_SCOPE_DEFINE_OPERAND(expr, type, var_name, repr_name) \
    MT_SCOPE_DEFINE(type var_name = (type) expr) \
    MT_SCOPE_DEFINE(const char *repr_name = #expr)

#define MT_SCOPE_BEFORE(expr) for (; __mt_enter_loop_flag && (expr, 1); __mt_enter_loop_flag = 0)
#define MT_SCOPE_AFTER(expr) for (; __mt_enter_loop_flag; __mt_enter_loop_flag = 0, expr)
