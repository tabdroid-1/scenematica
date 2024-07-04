#pragma once

#include <UI/MenuBase.h>

namespace Editor {

class EditorLayer;

class MainMenu : public MenuBase {
public:
    MainMenu(EditorLayer* editorLayer);

    void OnEnter() override;
    void OnExit() override;
    void OnImGuiRender() override;
};

}
