#pragma once

#include "MaineCoon/Core/PlatformDetection.h"

#include <memory>

#if defined(MC_PLATFORM_WINDOWS)
#define MC_DEBUGBREAK() __debugbreak()
#elif defined(MC_PLATFORM_LINUX)
#include <signal.h>
#define MC_DEBUGBREAK() raise(SIGTRAP)
#elif defined(MC_PLATFORM_MACOS)
#include <signal.h>
#define MC_DEBUGBREAK() raise(SIGTRAP)
#elif defined(MC_PLATFORM_ANDROID)
#define MC_DEBUGBREAK() __builtin_trap()
#elif defined(MC_PLATFORM_WEB)
#define MC_DEBUGBREAK() EM_ASM({ debugger; });
#else
#error "Platform doesn't support debugbreak yet!"
#endif

#ifdef MC_DEBUG
#define MC_ENABLE_ASSERTS
#endif

#ifndef MC_DIST
#define MC_ENABLE_VERIFY
#endif

#define MC_EXPAND_MACRO(x) x
#define MC_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define MC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace MaineCoon {

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Shared = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Shared<T> CreateShared(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T1, typename T2>
Shared<T1> ShareAs(Shared<T2>& ptr)
{
    return std::static_pointer_cast<T1>(ptr);
};

template <typename T1, typename T2>
Shared<T1> ShareAs(const Shared<T2>& ptr)
{
    return std::static_pointer_cast<T1>(ptr);
};

}

#include "MaineCoon/Core/Assert.h"
#include "MaineCoon/Core/Log/Log.h"
