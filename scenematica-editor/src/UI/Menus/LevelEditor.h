#pragma once

#include <Tabby.h>
#include <UI/Panels/ContentBrowser.h>
#include <UI/Panels/ElementHierarchyPanel.h>
#include <UI/Panels/ElementProperties.h>
#include <scenematica/types.h>
#include <UI/Menus/MenuBase.h>
#include <Core/CameraController.h>

namespace Editor {

class EditorLayer;

class LevelEditor : public MenuBase {
public:
    LevelEditor(EditorLayer* editorLayer);

    void OnEnter() override;
    void OnExit() override;
    void OnUpdate() override;
    void OnImGuiRender() override;
    void OnEvent(Tabby::Event& e);

private:
    CameraController m_Camera;

    Tabby::Shared<Tabby::Framebuffer> m_Framebuffer;
    glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };
    glm::vec2 m_ViewportBounds[2];
    bool m_ViewportFocused = false, m_ViewportHovered = false;

    ContentBrowser m_ContentBrowserPanel;
    ElementHierarchyPanel m_ElementHierarchyPanel;
    ElementPropertiesPanel m_ElementPropertiesPanel;
};

}
