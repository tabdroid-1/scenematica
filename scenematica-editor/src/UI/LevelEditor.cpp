#include <UI/LevelEditor.h>
#include <MaineCoon.h>
#include <EditorLayer.h>
#include <scenematica/level.h>

namespace Editor {

LevelEditor::LevelEditor(EditorLayer* editorLayer)
    : MenuBase(editorLayer)
{
}

void LevelEditor::OnEnter()
{
    MaineCoon::Application::Get().SetMenubarCallback([this]() {
        if (ImGui::BeginMenu("File")) {
            // if (ImGui::MenuItem("Create New Registry")) {
            //     m_EditorLayer->CreateNewRegistry();
            // }

            // if (ImGui::MenuItem("Load Registry")) {
            //     m_EditorLayer->LoadRegistry();
            // }

            if (ImGui::MenuItem("Go to level list")) {
                MC_TRACE("State swtiched to level list");
                m_EditorLayer->SetEditorState(EditorLayer::LevelList);
            }

            if (ImGui::MenuItem("Save As Json")) {
                m_EditorLayer->SaveAsJson();
            }

            if (ImGui::MenuItem("Exit")) {
                MaineCoon::Application::Get().Close();
            }
            ImGui::EndMenu();
        }
    });
}

void LevelEditor::OnExit()
{
}

void LevelEditor::OnImGuiRender()
{
    if (!m_EditorLayer->m_CurrentLevel) {
        MC_ERROR("Current level is null");
        m_EditorLayer->SetEditorState(EditorLayer::LevelList);
    }

    auto& level = m_EditorLayer->m_CurrentLevel;

    ImGui::Begin("Editor");

    ImGui::Text("Level name: %s", level->GetLevelName().c_str());
    ImGui::Text("Level path: %s", level->GetLevelPath().c_str());
    ImGui::Text("Level clear color: %f %f %f %f", level->GetLevelClearColor().r, level->GetLevelClearColor().g, level->GetLevelClearColor().b, level->GetLevelClearColor().a);

    ImGui::End();
}

}
