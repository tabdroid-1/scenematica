#pragma once

#include <MaineCoon/Core/Application.h>

extern MaineCoon::Application* MaineCoon::CreateApplication(ApplicationCommandLineArgs args);

#if defined(MC_PLATFORM_ANDROID)

#define SDL_MAIN_HANDLED
#include "../../../vendor/SDL2/include/SDL_main.h"
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

int SDL_main(int argc, char* argv[])
{
    return main(argc, argv);
}

#elif defined(MC_PLATFORM_LINUX)
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

#elif defined(MC_PLATFORM_WINDOWS)
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

#elif defined(MC_PLATFORM_MACOS)
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

#elif defined(MC_PLATFORM_WEB)

#include <emscripten.h>

void run()
{
    MaineCoon::Application::Get().Run();
}

int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    emscripten_set_main_loop((em_callback_func)run, 0, 1);

    delete app;
}
#endif
