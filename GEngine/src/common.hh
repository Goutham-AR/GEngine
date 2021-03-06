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

#if defined(_WIN32)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__linux__)
#define DEBUG_BREAK() __asm__ __volatile__("int3")
#endif

// Assertion Macros
#if defined(GE_DEBUG)
#define GE_ASSERT(x, ...)                                                                          \
    {                                                                                              \
        if (!(x))                                                                                  \
        {                                                                                          \
            ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                \
            ENGINE_LOG_ERROR("Line: {0}, File: {1}, Function: {2}", __LINE__, __FILE__, __func__); \
            DEBUG_BREAK();                                                                         \
        }                                                                                          \
    }
#else
#define GE_ASSERT(x, ...)
#endif

#include <memory>
#include <glm/vec4.hpp>
namespace GE
{
template <typename T>
using Sptr = std::shared_ptr<T>;

template <typename T>
using Uptr = std::unique_ptr<T>;

using Color = glm::vec4;

}

// #define GE_PROFILE

// template <typename T>
// using Wptr = std::weak_ptr<T>;
