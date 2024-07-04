#include "Math.h"
#include "mcpch.h"

namespace MaineCoon::Math {

float Abs(float f)
{
    if (f > 0)
        return f;
    else
        return f * -1;
}

}
