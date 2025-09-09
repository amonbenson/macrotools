#pragma once


#define __MT_CONCAT(a, b) a ## b
#define MT_CONCAT(a, b) __MT_CONCAT(a, b)

#define __MT_STRINGIFY(x) #x
#define MT_STRINGIFY(x) __MT_STRINGIFY(x)


#define MT_UNIQUE_LABEL(x) MT_CONCAT(x, __COUNTER__)
#define MT_LINE_LABEL(x) MT_CONCAT(x, __LINE__)

#define MT_NUMARGS(...)  (sizeof((void *[]) { __VA_ARGS__ }) / sizeof(void *))
