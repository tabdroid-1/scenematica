#include "MaineCoon/Core/Window.h"
#include "mcpch.h"

#ifdef MC_PLATFORM_WINDOWS
#include "Platforms/Windows/WindowsWindow.h"
#elif defined(MC_PLATFORM_LINUX)
#include "Platforms/Linux/LinuxWindow.h"
#elif defined(MC_PLATFORM_MACOS)
#include "Platforms/MacOS/MacOSWindow.h"
#elif defined(MC_PLATFORM_WEB)
#include "Platforms/Web/WebWindow.h"
#elif defined(MC_PLATFORM_ANDROID)
#include "Platforms/Android/AndroidWindow.h"
#endif

namespace MaineCoon {
Scope<Window> Window::Create(const WindowProps& props)
{
#ifdef MC_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#elif defined(MC_PLATFORM_LINUX)
    return CreateScope<LinuxWindow>(props);
#elif defined(MC_PLATFORM_MACOS)
    return CreateScope<MacOSWindow>(props);
#elif defined(MC_PLATFORM_WEB)
    return CreateScope<WebWindow>(props);
#elif defined(MC_PLATFORM_ANDROID)
    return CreateScope<AndroidWindow>(props);
#else
    MC_CORE_ASSERT_TAGGED(false, "Unknown platform!");
    return nullptr;
#endif
}

}
