#pragma once

#include "MaineCoon/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <filesystem>
// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace MaineCoon {
class Log {
public:
    static void Init();

    static Shared<spdlog::logger>& GetCoreLogger()
    {
        return s_CoreLogger;
    }
    static Shared<spdlog::logger>& GetClientLogger()
    {
        return s_ClientLogger;
    }

private:
    static Shared<spdlog::logger> s_CoreLogger;
    static Shared<spdlog::logger> s_ClientLogger;
};
}

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
    return os << glm::to_string(quaternion);
}

// Core log macros
#define MC_CORE_TRACE(...) ::MaineCoon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MC_CORE_INFO(...) ::MaineCoon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MC_CORE_WARN(...) ::MaineCoon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MC_CORE_ERROR(...) ::MaineCoon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MC_CORE_CRITICAL(...) ::MaineCoon::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MC_TRACE(...) ::MaineCoon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MC_INFO(...) ::MaineCoon::Log::GetClientLogger()->info(__VA_ARGS__)
#define MC_WARN(...) ::MaineCoon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MC_ERROR(...) ::MaineCoon::Log::GetClientLogger()->error(__VA_ARGS__)
#define MC_CRITICAL(...) ::MaineCoon::Log::GetClientLogger()->critical(__VA_ARGS__)
