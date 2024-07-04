#pragma once

#include <UI/MenuBase.h>

namespace Editor {

class EditorLayer;

class LevelList : public MenuBase {
public:
    LevelList(EditorLayer* editorLayer);

    void OnEnter() override;
    void OnExit() override;
    void OnImGuiRender() override;
};

}
