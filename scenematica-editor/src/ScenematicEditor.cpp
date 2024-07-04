#include <MaineCoon/Core/Application.h>
#include <MaineCoon/Core/EntryPoint.h>
#include <EditorLayer.h>

class Sandbox : public MaineCoon::Application {
public:
    Sandbox(const MaineCoon::ApplicationSpecification& specification)
        : MaineCoon::Application(specification)
    {
        PushLayer(new Editor::EditorLayer());
    }

    ~Sandbox()
    {
    }
};

MaineCoon::Application* MaineCoon::CreateApplication(MaineCoon::ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name = "Scenematica Level Editor";
    spec.WorkingDirectory = "assets";
    spec.CommandLineArgs = args;
    spec.maxFPS = 120.0f;

    Application* app = new Sandbox(spec);

    return app;
}
