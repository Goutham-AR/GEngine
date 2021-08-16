#pragma once

#if defined(_WIN32)
#if defined(GE_BUILD_DLL)
#if defined(GE_ENABLE_EXPORT)
#define GE_PUBLIC __declspec(dllexport)
#else
#define GE_PUBLIC __declspec(dllimport)
#endif // GE_ENABLE_EXPORT
#else  // GE_BUILD_DLL
#define GE_PUBLIC
#endif                   // GE_BUILD_DLL
#elif defined(__linux__) // _WIN32
#define GE_PUBLIC
#endif // _WIN32

#define BIT(x) (1 << x)

// Assertion Macros
#if defined(GE_DEBUG)
#define GE_ASSERT(x, ...)                                                                          \
    {                                                                                              \
        if (!(x))                                                                                  \
        {                                                                                          \
            ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                \
            ENGINE_LOG_ERROR("Line: {0}, File: {1}, Function: {2}", __LINE__, __FILE__, __func__); \
            std::exit(1);                                                                          \
        }                                                                                          \
    }
#else
#define GE_ASSERT(x, ...)
#endif

#include <memory>

namespace GE
{
template <typename T>
using Sptr = std::shared_ptr<T>;

template <typename T>
using Uptr = std::unique_ptr<T>;
}

// template <typename T>
// using Wptr = std::weak_ptr<T>;
