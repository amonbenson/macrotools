#pragma once


#ifndef FMT_GENERIC
    #define FMT_GENERIC 1
#endif


#define _FMT_STRINGIFY(x) #x
#define FMT_STRINGIFY(x) _FMT_STRINGIFY(x)


#if FMT_GENERIC
    #define FMT_SPECIFIER(x) _Generic((x), \
        _Bool: "%s", \
        unsigned char: "0x%02x", \
        char: "%c", \
        signed char: "%c", \
        short int: "%d", \
        unsigned short int: "%u", \
        int: "%d", \
        unsigned int: "%u", \
        long int: "%ld", \
        unsigned long int: "%lu", \
        long long int: "%ld", \
        unsigned long long int: "%lu", \
        float: "%f", \
        double: "%f", \
        long double: "%Lf", \
        default: "%p")
#else
    #define FMT_SPECIFIER(x) FMT_SOURCE_S
#endif

#if FMT_GENERIC
    #define FMT_VALUE(x, ...) (_Generic((x), \
        _Bool: ((x) ? "true" : "false"), \
        unsigned char: (x), \
        char: (x), \
        signed char: (x), \
        short int: (x), \
        unsigned short int: (x), \
        int: (x), \
        unsigned int: (x), \
        long int: (x), \
        unsigned long int: (x), \
        long long int: (x), \
        unsigned long long int: (x), \
        float: (x), \
        double: (x), \
        long double: (x), \
        default: (x)))
#else
    #define FMT_VALUE(x) FMT_SOURCE_F
#endif
