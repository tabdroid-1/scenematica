#include <EditorLayer.h>
#include <UI/MenuBase.h>
#include <UI/MainMenu.h>
#include <UI/LevelList.h>
#include <UI/LevelEditor.h>

namespace Editor {

EditorLayer::EditorLayer()
    : m_State(MainMenu)
{
    m_EditorMenus[MainMenu] = MaineCoon::CreateShared<Editor::MainMenu>(this);
    m_EditorMenus[LevelList] = MaineCoon::CreateShared<Editor::LevelList>(this);
    m_EditorMenus[LevelEditor] = MaineCoon::CreateShared<Editor::LevelEditor>(this);
}

void EditorLayer::OnImGuiRender()
{
    MC_PROFILE_SCOPE_NAME("EditorLayer::OnImGuiRender()");
    m_EditorMenus[m_State]->OnImGuiRender();
}

void EditorLayer::SetEditorState(EditorState state)
{
    MC_PROFILE_SCOPE_NAME("EditorLayer::SetEditorState()");
    if (state != m_State) {
        m_EditorMenus[m_State]->OnExit();
        m_State = state;
        m_EditorMenus[m_State]->OnEnter();
    }
}

void EditorLayer::LoadRegistry()
{
    MC_PROFILE_SCOPE_NAME("EditorLayer::LoadRegistry()");
    std::string path = MaineCoon::FileDialogs::OpenFile(".smlr");

    if (path != "") {

        m_CurrentLevelRegistry = MaineCoon::CreateShared<Scenematica::LevelRegistry>(path);
        MC_TRACE("Loaded Registry");
        SetEditorState(EditorLayer::LevelList);
    } else {

        MC_WARN("File dialog closed or path not found");
    }
}

void EditorLayer::CreateNewRegistry()
{
    MC_PROFILE_SCOPE_NAME("EditorLayer::CreateNewRegistry()");
    m_CurrentLevelRegistry = MaineCoon::CreateShared<Scenematica::LevelRegistry>();
    MC_TRACE("Created New Registry");
    SetEditorState(EditorLayer::LevelList);
}

void EditorLayer::SetCurrentLevel(const std::string& levelName)
{
    MC_PROFILE_SCOPE_NAME("EditorLayer::SetCurrentLevel");
    auto& levels = m_CurrentLevelRegistry->GetLevelMap();
    if (levels.find(levelName) != levels.end()) {
        m_CurrentLevel = levels[levelName];
        MC_TRACE("Set current level: {0}", levelName);
    }
}

void EditorLayer::CreateLevel(const std::string& levelName)
{
    MC_PROFILE_SCOPE_NAME("EditorLayer::SetCurrentLevel");
    auto& levels = m_CurrentLevelRegistry->GetLevelMap();
    if (levels.find(levelName) == levels.end()) {

        levels[levelName] = MaineCoon::CreateShared<Scenematica::Level>(levelName);
        MC_TRACE("Created level {0}", levelName);
    }
}

void EditorLayer::DeleteLevel(const std::string& levelName)
{
    auto& levels = m_CurrentLevelRegistry->GetLevelMap();
    if (levels.find(levelName) != levels.end()) {
        levels.erase(levelName);
        MC_TRACE("Deleted level \"{0}\"", levelName);
    }
}

void EditorLayer::SaveAsJson()
{
    std::string path = MaineCoon::FileDialogs::SaveFile(".smlrj");

    if (path == "") {
        MC_ERROR("File dialog closed or path not found");
        return;
    }

    Scenematica::LevelRegistry::SerializeToJson(*m_CurrentLevelRegistry, path);
    MC_TRACE("Saved registry \"{0}\"", m_CurrentLevelRegistry->GetRegistryName());
}

}
