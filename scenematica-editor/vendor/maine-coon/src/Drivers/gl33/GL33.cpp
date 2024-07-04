
#include "Drivers/gl33/GL33.h"
#if !defined(MC_PLATFORM_WEB) || !defined(MC_PLATFORM_ANDROID)
#include <glad/gl33.h>

namespace MaineCoon {

GL33* GL33::s_Instance = nullptr;
GladGLContext* GL33::gl = nullptr;

GL33::GL33()
{
    MC_CORE_ASSERT_TAGGED(!s_Instance, "GL33 context already exists!");
    s_Instance = this;
}

void GL33::Init(GladGLContext* context)
{
    if (!s_Instance) {
        s_Instance = new GL33();
    }

    s_Instance->gl = context;
}

}
#endif
