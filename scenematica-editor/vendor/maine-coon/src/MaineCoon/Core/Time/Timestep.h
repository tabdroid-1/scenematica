#pragma once

namespace MaineCoon {

class Timestep {
public:
    Timestep(float time = 0.0f)
        : m_Time(time)
    {
    }

    operator double() const
    {
        return m_Time;
    }

    double GetSeconds() const { return m_Time; }
    double GetMilliseconds() const { return m_Time * 1000.0f; }

private:
    // static Timestep* s_Instance;
    double m_Time;
};

}
