#include "Drivers/gles3/OpenGLES3RendererAPI.h"
#include "Drivers/gles3/GLES3.h"
#include "mcpch.h"

#include <glad/gles3.h>

namespace MaineCoon {

// void OpenGLMessageCallback(
//     unsigned source,
//     unsigned type,
//     unsigned id,
//     unsigned severity,
//     int length,
//     const char* message,
//     const void* userParam)
// {
//     switch (severity) {
//         // case GL_DEBUG_SEVERITY_HIGH:         MC_CORE_CRITICAL(message); return;
//         // case GL_DEBUG_SEVERITY_MEDIUM:       MC_CORE_ERROR(message); return;
//         // case GL_DEBUG_SEVERITY_LOW:          MC_CORE_WARN(message); return;
//         // case GL_DEBUG_SEVERITY_NOTIFICATION: MC_CORE_TRACE(message); return;
//     }
//
//     MC_CORE_ASSERT(false, "Unknown severity level!");
// }

void OpenGLES3RendererAPI::Init()
{
    // MC_PROFILE_FUNCTION();

#ifdef MC_DEBUG
    // glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    //
    // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

    GLES3::GL()->Enable(GL_BLEND);
    GLES3::GL()->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLES3::GL()->Enable(GL_DEPTH_TEST);
    // glEnable(GL_LINE_SMOOTH);
}

void OpenGLES3RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    GLES3::GL()->Viewport(x, y, width, height);
}

void OpenGLES3RendererAPI::SetClearColor(const glm::vec4& color)
{
    GLES3::GL()->ClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLES3RendererAPI::Clear()
{
    GLES3::GL()->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
