#include <Tabby/Core/Time/Timestep.h>

#include <UI/Menus/LevelEditor.h>
#include <EditorLayer.h>
#include <scenematica/level.h>
#include <imgui/imgui.h>

namespace Editor {

LevelEditor::LevelEditor(EditorLayer* editorLayer)
    : MenuBase(editorLayer)
    , m_Camera(2560.0f / 1600.0f, true)
    , m_ElementHierarchyPanel(editorLayer)
    , m_ElementPropertiesPanel(editorLayer)
{
}

void LevelEditor::OnEnter()
{

    m_EditorLayer->SetMenubarCallback([this]() {
        if (ImGui::BeginMenu("File")) {
            // if (ImGui::MenuItem("Create New Registry")) {
            //     m_EditorLayer->CreateNewRegistry();
            // }

            // if (ImGui::MenuItem("Load Registry")) {
            //     m_EditorLayer->LoadRegistry();
            // }

            if (ImGui::MenuItem("Go to level list")) {
                TB_TRACE("State swtiched to level list");
                m_EditorLayer->SetEditorState(EditorLayer::LevelList);
            }

            if (ImGui::MenuItem("Save As Json")) {
                m_EditorLayer->SaveAsJson();
            }

            if (ImGui::MenuItem("Exit")) {
                Tabby::Application::Get().Close();
            }
            ImGui::EndMenu();
        }
    });

    Tabby::FramebufferSpecification fbSpec;
    fbSpec.Attachments = { Tabby::FramebufferTextureFormat::RGBA8, Tabby::FramebufferTextureFormat::RED_INTEGER, Tabby::FramebufferTextureFormat::DEPTH24STENCIL8 };
    fbSpec.Width = 2560;
    fbSpec.Height = 1600;
    m_Framebuffer = Tabby::Framebuffer::Create(fbSpec);
}

void LevelEditor::OnExit()
{
}

void LevelEditor::OnUpdate()
{
    m_Camera.OnResize(m_ViewportSize.x, m_ViewportSize.y);
    m_Camera.OnUpdate();

    if (Tabby::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
        m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
        (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
        m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    }

    Tabby::Renderer2D::ResetStats();

    m_Framebuffer->Bind();
    {
        TB_PROFILE_SCOPE_NAME("Renderer Prep");

        auto clearColor = m_EditorLayer->m_CurrentLevel->GetLevelClearColor();
        Tabby::RenderCommand::SetClearColor({ clearColor.r, clearColor.g, clearColor.b, clearColor.a });
        Tabby::RenderCommand::Clear();
    }

    Tabby::Renderer2D::BeginScene(m_Camera.GetCamera(), m_Camera.GetTransform().GetTransform());

    Tabby::Renderer2D::DrawQuad({ 0.3f, 0.0f, 0.0f }, { 0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    Tabby::Renderer2D::DrawQuad({ -0.3f, 0.0f, 0.0f }, { 0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f });

    Tabby::Renderer2D::EndScene();

    // RENDER

    m_Framebuffer->Unbind();
}

void LevelEditor::OnImGuiRender()
{
    if (!m_EditorLayer->m_CurrentLevel) {
        TB_ERROR("Current level is null");
        m_EditorLayer->SetEditorState(EditorLayer::LevelList);
    }

    auto& level = m_EditorLayer->m_CurrentLevel;

    { // Viewport
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // Disable padding
        ImGui::Begin("Viewport");
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();

        Tabby::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID(0);
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2 { m_ViewportSize.x, m_ViewportSize.y }, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });

        ImGui::End();
        ImGui::PopStyleVar();
    }

    { // Panels

        m_ElementPropertiesPanel.SetElement(m_ElementHierarchyPanel.GetSelectedElement(), m_ElementHierarchyPanel.IsElementSelected());

        m_ContentBrowserPanel.OnImGuiRender();
        m_ElementHierarchyPanel.OnImGuiRender();
        m_ElementPropertiesPanel.OnImGuiRender();
    }
}

void LevelEditor::OnEvent(Tabby::Event& e)
{
    m_Camera.OnEvent(e);
}

}
