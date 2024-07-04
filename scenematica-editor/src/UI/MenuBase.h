#pragma once

namespace Editor {

class EditorLayer;

class MenuBase {
public:
    MenuBase(EditorLayer* editorLayer)
        : m_EditorLayer(editorLayer)
    {
    }

    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;

    virtual void OnImGuiRender() = 0;

protected:
    EditorLayer* m_EditorLayer;
};

}
