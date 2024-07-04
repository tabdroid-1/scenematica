#pragma once

#include <MaineCoon.h>
#include <MaineCoon/Audio/AudioEngine.h>
#include <scenematica/level_registry.h>
#include <scenematica/level.h>

namespace Editor {

class MenuBase;

class EditorLayer : public MaineCoon::Layer {
public:
    EditorLayer();

    enum EditorState {
        MainMenu = 0,
        LevelList,
        LevelEditor
    };

    virtual void OnImGuiRender() override;

    void CreateNewRegistry();
    void LoadRegistry();

    void SetCurrentLevel(const std::string& levelName);
    void CreateLevel(const std::string& levelName);
    void DeleteLevel(const std::string& levelName);

    void SaveAsJson();

    void SetEditorState(EditorState state);

    MaineCoon::Shared<Scenematica::Level> m_CurrentLevel;
    MaineCoon::Shared<Scenematica::LevelRegistry> m_CurrentLevelRegistry;

private:
    EditorState m_State;

    std::unordered_map<EditorState, MaineCoon::Shared<Editor::MenuBase>> m_EditorMenus;
};

}
