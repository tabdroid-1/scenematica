#ifdef MC_PLATFORM_LINUX

#include "Platforms/Linux/LinuxWindow.h"
#include "mcpch.h"

#include "MaineCoon/Core/Input/Input.h"
#include "backends/imgui_impl_sdl2.h"

#include "MaineCoon/Core/Events/ApplicationEvent.h"
#include "MaineCoon/Core/Events/KeyEvent.h"
#include "MaineCoon/Core/Events/MouseEvent.h"

#include "MaineCoon/Renderer/Renderer.h"

#include <SDL.h>

namespace MaineCoon {

static uint8_t s_SDLWindowCount = 0;

LinuxWindow::LinuxWindow(const WindowProps& props)
{
    MC_PROFILE_SCOPE();

    Init(props);
}

LinuxWindow::~LinuxWindow()
{
    MC_PROFILE_SCOPE();

    Shutdown();
}

void LinuxWindow::Init(const WindowProps& props)
{
    MC_PROFILE_SCOPE();

    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    MC_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (s_SDLWindowCount == 0) {
        MC_PROFILE_SCOPE_NAME("SDL Init");
        int success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
        MC_CORE_ASSERT_TAGGED(success + 1, "Could not initialize SDL2!");
    }

    {
        MC_PROFILE_SCOPE_NAME("SDLCreateWindow");
        if (Renderer::GetAPI() == RendererAPI::API::OpenGL33) {

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#if defined(MC_DEBUG)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
        } else if (Renderer::GetAPI() == RendererAPI::API::OpenGLES3) {

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#if defined(MC_DEBUG)
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
        }
        m_Window = SDL_CreateWindow(
            m_Data.Title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            props.Width, props.Height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        ++s_SDLWindowCount;
    }

    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();

    SDL_SetWindowData(m_Window, "WindowData", &m_Data);
    SetVSync(false);

    Input::Init();
}

void LinuxWindow::Shutdown()
{
    MC_PROFILE_SCOPE();

    SDL_DestroyWindow(m_Window);
    --s_SDLWindowCount;

    if (s_SDLWindowCount == 0) {
        SDL_Quit();
    }
}

void LinuxWindow::OnUpdate()
{
    MC_PROFILE_SCOPE();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type) {
        case SDL_WINDOWEVENT: {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                m_Data.Width = event.window.data1;
                m_Data.Height = event.window.data2;
                WindowResizeEvent resizeEvent(m_Data.Width, m_Data.Height);
                m_Data.EventCallback(resizeEvent);
            }
            break;
        }

        case SDL_QUIT: {
            WindowCloseEvent closeEvent;
            m_Data.EventCallback(closeEvent);
            break;
        }

        case SDL_KEYDOWN: {
            if (event.key.repeat == 0) {
                KeyPressedEvent keyPressedEvent(event.key.keysym.scancode, false);
                m_Data.EventCallback(keyPressedEvent);
            }
            break;
        }

        case SDL_KEYUP: {
            KeyReleasedEvent keyReleasedEvent(event.key.keysym.scancode);
            m_Data.EventCallback(keyReleasedEvent);
            break;
        }

        case SDL_TEXTINPUT: {
            KeyTypedEvent keyTypedEvent(event.text.text[0]);
            m_Data.EventCallback(keyTypedEvent);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            if (event.button.state == SDL_PRESSED) {
                MouseButtonPressedEvent mouseButtonPressedEvent(event.button.button);
                m_Data.EventCallback(mouseButtonPressedEvent);
            }
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            if (event.button.state == SDL_RELEASED) {
                MouseButtonReleasedEvent mouseButtonReleasedEvent(event.button.button);
                m_Data.EventCallback(mouseButtonReleasedEvent);
            }
            break;
        }

        case SDL_MOUSEMOTION: {
            MouseMovedEvent mouseMovedEvent(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
            m_Data.EventCallback(mouseMovedEvent);
            break;
        }

        case SDL_MOUSEWHEEL: {
            MouseScrolledEvent mouseScrolledEvent(static_cast<float>(event.wheel.x), static_cast<float>(event.wheel.y));
            m_Data.EventCallback(mouseScrolledEvent);
            break;
        }
        }
    }

    m_Context->SwapBuffers();
}

void LinuxWindow::SetVSync(bool enabled)
{
    MC_PROFILE_SCOPE();

    if (enabled)
        SDL_GL_SetSwapInterval(1);
    else
        SDL_GL_SetSwapInterval(0);

    m_Data.VSync = enabled;
}

bool LinuxWindow::IsVSync() const
{
    return m_Data.VSync;
}
}

#endif
