#include "Yoru/Core/Core.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Yoru
{
    class Log
    {
        public:
            static void Init();

            inline static Ref<spdlog::logger> &GetCoreLogger()
            {
                return s_CoreLogger;
            }

            inline static Ref<spdlog::logger> &GetClientLogger()
            {
                return s_ClientLogger;
            }

        private:
            static Ref<spdlog::logger> s_CoreLogger;
            static Ref<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define Y_CORE_TRACE(...)    ::Yoru::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define Y_CORE_INFO(...)     ::Yoru::Log::GetCoreLogger()->info(__VA_ARGS__)
#define Y_CORE_WARN(...)     ::Yoru::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define Y_CORE_ERROR(...)    ::Yoru::Log::GetCoreLogger()->error(__VA_ARGS__)
#define Y_CORE_CRITICAL(...) ::Yoru::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define Y_TRACE(...)         ::Yoru::Log::GetClientLogger()->trace(__VA_ARGS__)
#define Y_INFO(...)          ::Yoru::Log::GetClientLogger()->info(__VA_ARGS__)
#define Y_WARN(...)          ::Yoru::Log::GetClientLogger()->warn(__VA_ARGS__)
#define Y_ERROR(...)         ::Yoru::Log::GetClientLogger()->error(__VA_ARGS__)
#define Y_CRITICAL(...)      ::Yoru::Log::GetClientLogger()->critical(__VA_ARGS__)