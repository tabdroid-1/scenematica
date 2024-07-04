#pragma once

#include "MaineCoon/Renderer/GraphicsContext.h"

struct SDL_Window;

namespace MaineCoon {

class OpenGL33Context : public GraphicsContext {
public:
    OpenGL33Context(SDL_Window* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;

private:
    SDL_Window* m_WindowHandle;
};

}
