#include "MaineCoon/Renderer/Renderer.h"
#include <MaineCoon/Core/Input/Input.h>

#include "MaineCoon/Utils/PlatformUtils.h"
#include <MaineCoon/Asset/AssetManager.h>
#include <MaineCoon/Audio/AudioEngine.h>
#include <imgui.h>

namespace MaineCoon {

Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecification& specification)
    : m_Specification(specification)
{
    MC_PROFILE_SCOPE();

    MC_CORE_ASSERT_TAGGED(!s_Instance, "Application already exists!");
    s_Instance = this;

    if (!m_Specification.WorkingDirectory.empty())
        std::filesystem::current_path(m_Specification.WorkingDirectory);

    m_Window = Window::Create(WindowProps(m_Specification.Name));
    m_Window->SetEventCallback(MC_BIND_EVENT_FN(Application::OnEvent));

    AssetManager::Init();
    Audio::Engine::Init();
    Renderer::Init();
    Input::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
    MC_PROFILE_SCOPE();
    Audio::Engine::Shutdown();
    Renderer::Shutdown();

    AssetManager::Get()->FullUnload();
    AssetManager::Shutdown();
}

void Application::PushLayer(Layer* layer)
{
    MC_PROFILE_SCOPE();

    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    MC_PROFILE_SCOPE();

    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::Close()
{
    m_Running = false;
}

void Application::SubmitToMainThread(const std::function<void()>& function)
{
    std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

    m_MainThreadQueue.emplace_back(function);
}

void Application::OnEvent(Event& e)
{
    MC_PROFILE_SCOPE();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(MC_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(MC_BIND_EVENT_FN(Application::OnWindowResize));

    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
        if (e.Handled)
            break;
        (*it)->OnEvent(e);
    }
}

void Application::Run()
{

    while (m_Running) {
        MC_PROFILE_FRAME("Application");

        double time = Time::GetTime();
        Time::SetDeltaTime(time - m_LastFrameTime);
        m_LastFrameTime = time;

        ExecuteMainThreadQueue();

        if (!m_Minimized && Time::GetDeltaTime() < 200.0f) { // ts < 200  because ts is really high number in first frame
            // and that breaks the phyiscs and some other stuff.
            // this happens because m_LastFrameTime is 0 in first frame.
            {
                MC_PROFILE_SCOPE_NAME("LayerStack OnUpdate");

                // TODO: Remove TimeStep
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(Time::GetDeltaTime());
            }

            m_ImGuiLayer->Begin();
            {
                static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

                // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
                // because it would be confusing to have two docking targets within each others.
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
                if (m_MenubarCallback)
                    window_flags |= ImGuiWindowFlags_MenuBar;

                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                // window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

                // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
                // and handle the pass-thru hole, so we ask Begin() to not render a background.
                if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                    window_flags |= ImGuiWindowFlags_NoBackground;

                // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
                // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
                // all active windows docked into it will lose their parent and become undocked.
                // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
                // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
                ImGui::Begin("DockSpace Demo", nullptr, window_flags);
                ImGui::PopStyleVar();

                ImGui::PopStyleVar(2);

                // Submit the DockSpace
                ImGuiIO& io = ImGui::GetIO();
                if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                    ImGuiID dockspace_id = ImGui::GetID("OpenGLAppDockspace");
                    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
                }

                if (m_MenubarCallback) {
                    if (ImGui::BeginMenuBar()) {
                        m_MenubarCallback();
                        ImGui::EndMenuBar();
                    }
                }

                {
                    MC_PROFILE_SCOPE_NAME("LayerStack OnImGuiRender");

                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();
                }
                ImGui::End();
            }
            m_ImGuiLayer->End();
        }

        m_Window->OnUpdate();

        // Framerate limiter. this will do nothing if maxFPS is 0.
        if (m_Specification.maxFPS > 0.0) {
            double frameTime = Time::GetTime() - time;

            double frameTimeLimit = 1.0 / m_Specification.maxFPS;
            if (frameTime < frameTimeLimit) {
                double sleepTime = frameTimeLimit - frameTime;
                std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            }
        }
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
    MC_PROFILE_SCOPE();

    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

void Application::ExecuteMainThreadQueue()
{
    std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

    for (auto& func : m_MainThreadQueue)
        func();

    m_MainThreadQueue.clear();
}

}
