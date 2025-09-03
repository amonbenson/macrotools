#pragma once

#ifndef MT_USE_COLOR
#define MT_USE_COLOR 1
#endif

#if MT_USE_COLOR
    #define MT_COLOR_RESET "\e[0m"

    #define MT_COLOR_RED "\e[1;31m"
    #define MT_COLOR_GREEN "\e[1;32m"
    #define MT_COLOR_YELLOW "\e[1;33m"
    #define MT_COLOR_BLUE "\e[1;34m"
    #define MT_COLOR_MAGENTA "\e[1;35m"
    #define MT_COLOR_CYAN "\e[1;36m"
    #define MT_COLOR_WHITE "\e[1;37m"

    #define MT_BACKGROUND_RED "\e[1;30;41m"
    #define MT_BACKGROUND_GREEN "\e[1;30;42m"
    #define MT_BACKGROUND_YELLOW "\e[1;30;43m"
    #define MT_BACKGROUND_BLUE "\e[1;30;44m"
    #define MT_BACKGROUND_MAGENTA "\e[1;30;45m"
    #define MT_BACKGROUND_CYAN "\e[1;30;46m"
    #define MT_BACKGROUND_WHITE "\e[1;30;47m"
#else
    #define MT_COLOR_RESET ""

    #define MT_COLOR_RED ""
    #define MT_COLOR_GREEN ""
    #define MT_COLOR_YELLOW ""
    #define MT_COLOR_BLUE ""
    #define MT_COLOR_MAGENTA ""
    #define MT_COLOR_CYAN ""
    #define MT_COLOR_WHITE ""

    #define MT_BACKGROUND_RED ""
    #define MT_BACKGROUND_GREEN ""
    #define MT_BACKGROUND_YELLOW ""
    #define MT_BACKGROUND_BLUE ""
    #define MT_BACKGROUND_MAGENTA ""
    #define MT_BACKGROUND_CYAN ""
    #define MT_BACKGROUND_WHITE ""
#endif
