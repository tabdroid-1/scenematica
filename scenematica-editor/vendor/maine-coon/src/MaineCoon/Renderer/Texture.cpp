#include "MaineCoon/Renderer/Texture.h"
#include "mcpch.h"

#include "Drivers/gl33/OpenGL33Texture.h"
#include "Drivers/gles3/OpenGLES3Texture.h"
#include "MaineCoon/Renderer/Renderer.h"
#include <MaineCoon/Foundation/Types.h>

namespace MaineCoon {

Shared<Texture> Texture::Create(const TextureSpecification& specification, AssetHandle handle, Buffer data)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        MC_CORE_ASSERT_TAGGED(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL33:
        return CreateShared<OpenGL33Texture>(specification, handle, data);
    case RendererAPI::API::OpenGLES3:
        return CreateShared<OpenGLES3Texture>(specification, handle, data);
    }

    MC_CORE_ASSERT_TAGGED(false, "Unknown RendererAPI!");
    return nullptr;
}

// Shared<Texture> Texture::Create(const std::string& path)
// {
//     switch (Renderer::GetAPI()) {
//     case RendererAPI::API::None:
//         MC_CORE_ASSERT_TAGGED(false, "RendererAPI::None is currently not supported!");
//         return nullptr;
//     case RendererAPI::API::OpenGL33:
//         return CreateShared<OpenGL33Texture>(path);
//     case RendererAPI::API::OpenGLES3:
//         return CreateShared<OpenGLES3Texture>(path);
//     }
//
//     MC_CORE_ASSERT_TAGGED(false, "Unknown RendererAPI!");
//     return nullptr;
// }

}
