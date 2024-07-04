#pragma once

#if !MC_PROFILE || defined(MC_PLATFORM_ANDROID)

#define MC_PROFILE_SCOPE()
#define MC_PROFILE_SCOPE_NAME(x)
#define MC_PROFILE_FRAME(x)
#define MC_PROFILE_TAG(y, x)
#define MC_PROFILE_LOG(text, size)
#define MC_PROFILE_VALUE(text, value)
#define MC_PROFILE_ALLOC(p, size)
#define MC_PROFILE_FREE(p)
#define MC_PROFILE_GPU(x)

#elif MC_PROFILE && !defined(MC_PLATFORM_ANDROID)
#define TRACY_ENABLE 1
#include "tracy/tracy/Tracy.hpp"
#include "tracy/tracy/TracyC.h"
#include "tracy/tracy/TracyOpenGL.hpp"

#define MC_PROFILE_SCOPE() ZoneScoped
#define MC_PROFILE_SCOPE_NAME(x) ZoneScopedN(x)
#define MC_PROFILE_FRAME(x) FrameMark
#define MC_PROFILE_TAG(y, x) ZoneText(x, strlen(x))
#define MC_PROFILE_LOG(text, size) TracyMessage(text, size)
#define MC_PROFILE_VALUE(text, value) TracyPlot(text, value)
#define MC_PROFILE_ALLOC(p, size) TracyCAllocS(p, size, 12)
#define MC_PROFILE_FREE(p) TracyCFreeS(p, 12)
#define MC_PROFILE_GPU(x) TracyGpuZone(x)

#endif
