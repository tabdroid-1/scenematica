#include <Tabby/Core/Application.h>
#include <Tabby/Core/EntryPoint.h>
#include <EditorLayer.h>

class Sandbox : public Tabby::Application {
public:
    Sandbox(const Tabby::ApplicationSpecification& specification)
        : Tabby::Application(specification)
    {
        PushLayer(new Editor::EditorLayer());
    }

    ~Sandbox()
    {
    }
};

Tabby::Application* Tabby::CreateApplication(Tabby::ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name = "Scenematica Level Editor";
    spec.WorkingDirectory = "assets";
    spec.CommandLineArgs = args;
    spec.maxFPS = 120.0f;

    Application* app = new Sandbox(spec);

    return app;
}
