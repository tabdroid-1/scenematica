#ifdef MC_PLATFORM_WEB

#include "MaineCoon/Core/Application.h"
#include "MaineCoon/Utils/PlatformUtils.h"
#include "tbpch.h"

#include <SDL.h>

namespace MaineCoon {

double Time::GetTime()
{
    using namespace std::chrono;
    system_clock::time_point currentTimePoint = system_clock::now();
    duration<double> timeSinceEpoch = currentTimePoint.time_since_epoch();

    double result = timeSinceEpoch.count();

    return result;
}

std::string FileDialogs::OpenFile(const char* filter)
{
    return std::string();
}

std::string FileDialogs::SaveFile(const char* filter)
{

    return std::string();
}

}

#endif
