#include "Drivers/gl33/OpenGL33RendererAPI.h"
#include "Drivers/gl33/GL33.h"
#include "mcpch.h"

#include <glad/gl33.h>

namespace MaineCoon {

void OpenGL33RendererAPI::Init()
{
    MC_PROFILE_SCOPE();

    GL33::GL()->Enable(GL_BLEND);
    GL33::GL()->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GL33::GL()->Enable(GL_DEPTH_TEST);
    GL33::GL()->Enable(GL_MULTISAMPLE);
}

void OpenGL33RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    GL33::GL()->Viewport(x, y, width, height);
}

void OpenGL33RendererAPI::SetClearColor(const glm::vec4& color)
{
    GL33::GL()->ClearColor(color.r, color.g, color.b, color.a);
}

void OpenGL33RendererAPI::Clear()
{
    GL33::GL()->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
