#pragma once

#if defined(_WIN32)
#if defined(GE_BUILD_DLL)
#if defined(GE_ENABLE_EXPORT)
#define GE_PUBLIC __declspec(dllexport)
#else
#define GE_PUBLIC __declspec(dllimport)
#endif // GE_ENABLE_EXPORT
#else // GE_BUILD_DLL
#define GE_PUBLIC
#endif // GE_BUILD_DLL
#elif defined(__linux__)    // _WIN32
#define GE_PUBLIC
#endif // _WIN32

#define BIT(x) (1 << x)

// Assertion Macros
#if defined(GE_DEBUG)
#define GE_ASSERT(x, ...)                                           \
    {                                                               \
        if (!(x))                                                   \
        {                                                           \
            ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            std::exit(1);                                           \
        }                                                           \
    }
#else
#define GE_ASSERT(x, ...)
#endif
