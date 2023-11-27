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