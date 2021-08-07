#pragma once

#if defined(_WIN32)

#if defined(GE_BUILD_DLL)
#define GE_PUBLIC __declspec(dllexport)
#else
#define GE_PUBLIC __declspec(dllimport)
#endif // GE_BUILD_DLL

#elif defined(__linux__)
#define GE_PUBLIC

#endif // _WIN32

#define BIT(x) (1 << x)

#if defined(GE_DEBUG)
#define GE_ASSERT(x, ...)                                           \
    {                                                               \
        if (!(x))                                                   \
        {                                                           \
            ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        }                                                           \
    }

#elif
#define GE_ASSERT(x, ...)
#endif
