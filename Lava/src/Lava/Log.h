#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Lava
{
    class LAVA_API Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core Logger Macros
#define LV_CORE_TRACE(...)  ::Lava::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LV_CORE_INFO(...)   ::Lava::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LV_CORE_WARN(...)   ::Lava::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LV_CORE_ERROR(...)  ::Lava::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LV_CORE_FATAL(...)  ::Lava::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Logger Macros
#define LV_TRACE(...)  ::Lava::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LV_INFO(...)   ::Lava::Log::GetClientLogger()->info(__VA_ARGS__)
#define LV_WARN(...)   ::Lava::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LV_ERROR(...)  ::Lava::Log::GetClientLogger()->error(__VA_ARGS__)
#define LV_FATAL(...)  ::Lava::Log::GetClientLogger()->critical(__VA_ARGS__) 
