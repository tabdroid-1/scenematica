#pragma once

#include "MaineCoon/Core/Base.h"

#include "MaineCoon/Core/Events/ApplicationEvent.h"
#include "MaineCoon/Core/Events/MouseEvent.h"
#include "MaineCoon/Core/Events/Event.h"
#include "MaineCoon/Core/Layer/LayerStack.h"
#include "MaineCoon/Core/Window.h"

#include "MaineCoon/UI/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace MaineCoon {

struct ApplicationCommandLineArgs {
    int Count = 0;
    char** Args = nullptr;

    const char* operator[](int index) const
    {
        MC_CORE_ASSERT(index < Count);
        return Args[index];
    }
};

struct ApplicationSpecification {
    std::string Name = "MaineCoon Application";
    std::string WorkingDirectory;
    ApplicationCommandLineArgs CommandLineArgs;
    float maxFPS = 0.0f;
};

class Application {
public:
    Application(const ApplicationSpecification& specification);
    virtual ~Application();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    Window& GetWindow() { return *m_Window; }

    void Close();

    ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

    static Application& Get() { return *s_Instance; }

    const ApplicationSpecification& GetSpecification() const { return m_Specification; }

    void SubmitToMainThread(const std::function<void()>& function);

    void Run();

    void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

    void ExecuteMainThreadQueue();

private:
    ApplicationSpecification m_Specification;
    Scope<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    LayerStack m_LayerStack;

    double m_LastFrameTime = 0.0f;
    bool m_Minimized = false;
    bool m_Running = true;

    std::function<void()> m_MenubarCallback;

    std::vector<std::function<void()>> m_MainThreadQueue;
    std::mutex m_MainThreadQueueMutex;

private:
    static Application* s_Instance;
    friend int ::main(int argc, char** argv);
};

// To be defined in CLIENT
Application* CreateApplication(ApplicationCommandLineArgs args);

}
