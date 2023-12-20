#pragma once

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

#define BIND_CLASS_EVENT(fn) std::bind((fn), this, std::placeholders::_1)

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