#include "Drivers/gl33/OpenGL33Context.h"
#include "Drivers/gl33/GL33.h"
#include "mcpch.h"

#include <tracy/tracy/TracyOpenGL.hpp>

// #if !defined(MC_PLATFORM_WEB) && !defined(TB_PLATFORM_ANDROID)
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl33.h>

#include <SDL.h>

namespace MaineCoon {

OpenGL33Context::OpenGL33Context(SDL_Window* windowHandle)
    : m_WindowHandle(windowHandle)
{
    MC_CORE_ASSERT_TAGGED(windowHandle, "Window handle is null!");
}

void OpenGL33Context::Init()
{
    MC_PROFILE_SCOPE();

    SDL_GLContext windowContext = SDL_GL_CreateContext(m_WindowHandle);
    SDL_GL_MakeCurrent(m_WindowHandle, windowContext);

    GladGLContext* context = (GladGLContext*)calloc(1, sizeof(GladGLContext));
    MC_CORE_ASSERT_TAGGED(context, "Failed to initialize GL33 context!");

    int status = gladLoadGLContext(context, (GLADloadfunc)SDL_GL_GetProcAddress);
    MC_CORE_ASSERT_TAGGED(status, "Failed to initialize Glad!");

    GL33::Init(context);

    // TracyGpuContext;

    MC_CORE_INFO("OpenGL Info:");
    MC_CORE_INFO("  Vendor: {0}", GL33::GL()->GetString(GL_VENDOR));
    MC_CORE_INFO("  Renderer: {0}", GL33::GL()->GetString(GL_RENDERER));
    MC_CORE_INFO("  Version: {0}", GL33::GL()->GetString(GL_VERSION));

    std::string version = reinterpret_cast<const char*>(GL33::GL()->GetString(GL_VERSION));
    size_t dotPosition = version.find('.');

    int major = std::stoi(version.substr(0, dotPosition));
    int minor = std::stoi(version.substr(dotPosition + 1));

    MC_CORE_ASSERT_TAGGED(major > 3 || (major == 3 && minor >= 3), "MaineCoon requires at least OpenGL version 3.3!");
}

void OpenGL33Context::SwapBuffers()
{
    MC_PROFILE_SCOPE();

    SDL_GL_SwapWindow(m_WindowHandle);

    // TracyGpuCollect;
}

}
// #endif
