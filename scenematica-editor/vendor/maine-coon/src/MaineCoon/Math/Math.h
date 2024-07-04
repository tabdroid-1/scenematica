#pragma once

#include <mcpch.h>

namespace MaineCoon::Math {

const float PI = 3.14159265358979323846f;
const float DEG2RAD = (PI / 180.0f);
const float RAD2DEG = (180.0f / PI);
const float EPSILON = 0.000001f;

float Abs(float f);

template <typename T>
inline bool IsPowerOf2(T value)
{
    if (!std::is_integral_v<T>)
        return false;

    bool result = value && ((value & (value - 1)) == 0);
    return result;
}

}
