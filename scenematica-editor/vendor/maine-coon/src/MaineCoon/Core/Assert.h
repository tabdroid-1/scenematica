#pragma once

#include "MaineCoon/Core/Base.h"
#include "MaineCoon/Core/Log/Log.h"

#define MC_CORE_VERIFY(expression)                                           \
    do {                                                                     \
        if (!(expression)) {                                                 \
            MC_CORE_ERROR("Assertion failed: {0}({1})", __FILE__, __LINE__); \
            MC_DEBUGBREAK();                                                 \
        }                                                                    \
    } while (false)
#define MC_CORE_VERIFY_TAGGED(expression, ...)      \
    do {                                            \
        if (!(expression)) {                        \
            MC_CORE_ERROR(                          \
                "Assertion failed: {0}({1}) | {2}", \
                __FILE__,                           \
                __LINE__,                           \
                __VA_ARGS__);                       \
            MC_DEBUGBREAK();                        \
        }                                           \
    } while (false)

#ifdef MC_ENABLE_ASSERTS

#define MC_CORE_ASSERT(expression)                                           \
    do {                                                                     \
        if (!(expression)) {                                                 \
            MC_CORE_ERROR("Assertion failed: {0}({1})", __FILE__, __LINE__); \
            MC_DEBUGBREAK();                                                 \
        }                                                                    \
    } while (false)
#define MC_CORE_ASSERT_TAGGED(expression, ...)      \
    do {                                            \
        if (!(expression)) {                        \
            MC_CORE_ERROR(                          \
                "Assertion failed: {0}({1}) | {2}", \
                __FILE__,                           \
                __LINE__,                           \
                __VA_ARGS__);                       \
            MC_DEBUGBREAK();                        \
        }                                           \
    } while (false)
#else
#define MC_CORE_ASSERT(expression)
#define MC_CORE_ASSERT_TAGGED(expression, ...)
#endif
