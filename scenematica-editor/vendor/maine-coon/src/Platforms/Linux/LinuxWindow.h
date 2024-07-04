#pragma once

#ifdef MC_PLATFORM_LINUX

#include "MaineCoon/Core/Window.h"
#include "MaineCoon/Renderer/GraphicsContext.h"

class SDL_Window;

namespace MaineCoon {

class LinuxWindow : public Window {
public:
    LinuxWindow(const WindowProps& props);
    virtual ~LinuxWindow();

    void OnUpdate() override;

    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    virtual void* GetNativeWindow() const { return m_Window; }

private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

private:
    SDL_Window* m_Window;
    Scope<GraphicsContext> m_Context;

    struct WindowData {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

}

#endif
