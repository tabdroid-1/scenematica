#include "MaineCoon/Renderer/GraphicsContext.h"
#include "mcpch.h"

#include "Drivers/gl33/OpenGL33Context.h"
#include "Drivers/gles3/OpenGLES3Context.h"
#include "MaineCoon/Renderer/Renderer.h"

namespace MaineCoon {

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        MC_CORE_ASSERT_TAGGED(false, "No renderer API selected.");
        return nullptr;
    case RendererAPI::API::OpenGL33:
        return CreateScope<OpenGL33Context>(static_cast<SDL_Window*>(window));
    case RendererAPI::API::OpenGLES3:
        return CreateScope<OpenGLES3Context>(static_cast<SDL_Window*>(window));
    }

    MC_CORE_ASSERT_TAGGED(false, "Unknown RendererAPI!");
    return nullptr;
}

}
