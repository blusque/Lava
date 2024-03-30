#pragma once

#include <memory>

#ifdef _WIN32
    #ifdef _WIN64
        /* x64 Platform */
        #ifndef LV_PLATFORM_WINDOWS
            #define LV_PLATFORM_WINDOWS
        #endif
    #else
        /* x86 Platform */
        #error "x86 Builder is not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
#elif defined(__ANDROID__)
#endif

#ifdef LV_PLATFORM_WINDOWS
    #ifdef LV_BUILD_DLL
        #define LAVA_API __declspec(dllexport)
    #else
        #define LAVA_API __declspec(dllimport)
    #endif
#else
    #error Lava only support windows now!
#endif

#define BIT(x) ( 1 << (x) )

#define BIND_CLASS_EVENT(fn) [this](auto&&... args) -> decltype(auto)\
    { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef LV_PLATFORM_WINDOWS
#define LV_DEBUG_BREAK() __debugbreak();
#elif LV_PLATFORM_LINUX
#define LV_DEBUG_BREAK() raise(SIGTAP); 
#endif

#ifdef LV_DEBUG
    #define LV_ASSERT(x, ...) if(!(x)) { LV_ERROR("AssertionFailed: {0}, File: {1}, Line: {2}",\
                                        __VA_ARGS__, __FILE__, __LINE__);\
                                        __debugbreak(); }
    #define LV_CORE_ASSERT(x, ...) if(!(x)) { LV_CORE_ERROR("AssertionFailed: {0}, File: {1}, Line: {2}",\
                                            __VA_ARGS__, __FILE__, __LINE__);\
                                            __debugbreak(); }
#else
    #define LV_ASSERT(x, ...)
    #define LV_CORE_ASSERT(x, ...)
#endif

#define _LV_CONCAT(x, y) x##y
#define _LV_STR(x) #x

// 2 Level Macro to use the marco function
#define LV_CONCAT(x, y) _LV_CONCAT(x, y)
#define LV_STR(x) _LV_STR(x)

namespace Lava
{
    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <class T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using WeakRef = std::weak_ptr<T>;

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <class T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}
