#pragma once

#include <UI/MenuBase.h>

namespace Editor {

class EditorLayer;

class LevelEditor : public MenuBase {
public:
    LevelEditor(EditorLayer* editorLayer);

    void OnEnter() override;
    void OnExit() override;
    void OnImGuiRender() override;
};

}
