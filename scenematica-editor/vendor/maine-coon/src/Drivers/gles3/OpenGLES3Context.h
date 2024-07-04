#pragma once

#include "MaineCoon/Renderer/GraphicsContext.h"

struct SDL_Window;

namespace MaineCoon {

class OpenGLES3Context : public GraphicsContext {
public:
    OpenGLES3Context(SDL_Window* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;

private:
    SDL_Window* m_WindowHandle;
};

}
