#ifdef MC_PLATFORM_MACOS

#include "MaineCoon/Utils/PlatformUtils.h"

namespace MaineCoon {

double Time::GetTime()
{
    using namespace std::chrono;
    system_clock::time_point currentTimePoint = system_clock::now();
    duration<double> timeSinceEpoch = currentTimePoint.time_since_epoch();

    double result = timeSinceEpoch.count();

    return result;
}

}

#endif
