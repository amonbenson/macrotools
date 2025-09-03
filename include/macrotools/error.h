#pragma once

#include "macrotools/log.h"


#ifndef ERROR_RETURN_TYPE
#define ERROR_RETURN_TYPE int
#endif

#ifndef ERROR_RETURN_VARIABLE
#define ERROR_RETURN_VARIABLE ret
#endif

#ifndef ERROR_EXIT_FUNCTION
#define ERROR_EXIT_FUNCTION exit(1)
#endif

#ifndef ERROR_CLEANUP_LABEL
#define ERROR_CLEANUP_LABEL cleanup
#endif


#define TRY_OR_RETURN(expr, format, ...) \
    do { \
        ERROR_RETURN_TYPE _ret; \
        if ((_ret = (expr)) != 0) { \
            LOG_ERROR("Error %d: " format, _ret, ##__VA_ARGS__); \
            return _ret; \
        } \
    } while (0)

#define TRY_OR_WARN(expr, format, ...) \
    do { \
        ERROR_RETURN_TYPE _ret; \
        if ((_ret = (expr)) != 0) { \
            LOG_WARN("Error %d: " format, _ret, ##__VA_ARGS__); \
        } \
    } while (0)

#define TRY_OR_EXIT(expr, format, ...) \
    do { \
        ERROR_RETURN_TYPE _ret; \
        if ((_ret = (expr)) != 0) { \
            LOG_ERROR("Error %d: " format, _ret, ##__VA_ARGS__); \
            ERROR_EXIT_FUNCTION; \
        } \
    } while (0)

#define TRY_OR_CLEANUP(expr, format, ...) \
    do { \
        if ((ERROR_RETURN_VARIABLE = (expr)) != 0) { \
            LOG_ERROR("Error %d: " format, ERROR_RETURN_VARIABLE, ##__VA_ARGS__); \
            goto ERROR_CLEANUP_LABEL; \
        } \
    } while (0)

#define _TRY_ASSERT(expr, ret, ...) ((expr) ? 0 : (ret))
#define TRY_ASSERT(expr, ...) _TRY_ASSERT(expr, ## __VA_ARGS__, 1)
