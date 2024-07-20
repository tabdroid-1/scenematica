#pragma once

namespace Scenematica {

class Color {
public:
    Color(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f)
        : r(red)
        , g(green)
        , b(blue)
        , a(alpha)
    {
    }

    float* Data()
    {
        return &r;
    }

    const float* Data() const
    {
        return &r;
    }

    float r, g, b, a;
};

class Vector2 {
public:
    Vector2(float x = 0.0f, float y = 0.0f)
    {
        this->x = x;
        this->y = y;
    }

    float* Data()
    {
        return &x;
    }

    const float* Data() const
    {
        return &x;
    }

    float x, y;
};

class Vector3 {
public:
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float* Data()
    {
        return &x;
    }

    const float* Data() const
    {
        return &x;
    }

    float x, y, z;
};

class Vector4 {
public:
    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    float* Data()
    {
        return &x;
    }

    const float* Data() const
    {
        return &x;
    }

    float x, y, z, w;
};

}
