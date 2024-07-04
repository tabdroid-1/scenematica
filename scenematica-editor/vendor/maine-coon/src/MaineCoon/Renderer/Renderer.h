#pragma once

#include <mcpch.h>

#include "MaineCoon/Renderer/RenderCommand.h"
#include "MaineCoon/Renderer/RendererAPI.h"

namespace MaineCoon {

class Renderer {
public:
    static void Init();
    static void Shutdown();

    static void OnWindowResize(uint32_t width, uint32_t height);

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};
}
