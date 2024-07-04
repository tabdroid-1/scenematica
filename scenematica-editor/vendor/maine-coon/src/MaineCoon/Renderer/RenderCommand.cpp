#include "MaineCoon/Renderer/RenderCommand.h"
#include "mcpch.h"

namespace MaineCoon {

Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
