#include <UI/MainMenu.h>
#include <MaineCoon.h>
#include <EditorLayer.h>

namespace Editor {

MainMenu::MainMenu(EditorLayer* editorLayer)
    : MenuBase(editorLayer)
{
}

void MainMenu::OnEnter()
{
    MaineCoon::Application::Get().SetMenubarCallback([this]() {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Create New Registry")) {
                m_EditorLayer->CreateNewRegistry();
            }

            if (ImGui::MenuItem("Load Registry")) {
                m_EditorLayer->LoadRegistry();
            }

            if (ImGui::MenuItem("Exit")) {
                MaineCoon::Application::Get().Close();
            }
            ImGui::EndMenu();
        }
    });
}

void MainMenu::OnExit()
{
    MaineCoon::Application::Get().SetMenubarCallback([]() {
    });
}

void MainMenu::OnImGuiRender()
{
    ImGui::Begin("Main Menu");

    if (ImGui::Button("Create New Registry", { 400.0f, 200.0f })) {
        m_EditorLayer->CreateNewRegistry();
    }

    if (ImGui::Button("Load Registry", { 400.0f, 200.0f })) {
        m_EditorLayer->LoadRegistry();
    }

    ImGui::End();
}

}
