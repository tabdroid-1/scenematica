#include "MaineCoon/Renderer/RendererAPI.h"
#include "mcpch.h"

#include "Drivers/gl33/OpenGL33RendererAPI.h"
#include "Drivers/gles3/OpenGLES3RendererAPI.h"

namespace MaineCoon {

#if defined(MC_PLATFORM_WEB) || defined(MC_PLATFORM_ANDROID)
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGLES3;
#else
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL33;
#endif

Scope<RendererAPI> RendererAPI::Create()
{
    switch (s_API) {
    case RendererAPI::API::None:
        MC_CORE_ASSERT_TAGGED(false, "No renderer API selected.");
        return nullptr;
    case RendererAPI::API::OpenGL33:
#if defined(MC_PLATFORM_WEB) || defined(MC_PLATFORM_ANDROID)
        MC_CORE_ASSERT_TAGGED(false, "Android/Web does not support OpenGL 3.3");
        return nullptr;
#else
        return CreateScope<OpenGL33RendererAPI>();
#endif
    case RendererAPI::API::OpenGLES3:
        return CreateScope<OpenGLES3RendererAPI>();
    }

    MC_CORE_ASSERT_TAGGED(false, "Unknown RendererAPI!");
    return nullptr;
}

}
