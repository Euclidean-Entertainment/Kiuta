/**
 * 
 */
#pragma once

#include <cmath>

class Angle final
{
public:
    Angle() {}
    Angle(float angle)
    : m_angle(angle) {}
    Angle(const Angle& angle)
    : m_angle(angle.m_angle) {}

    inline float radians() const
    {
        return m_angle * (M_PI / 180.0f);
    }

    void operator=(const Angle& rhs)
    {
        m_angle = rhs.m_angle;
    }

    inline float degrees() const
    {
        return m_angle;
    }

    const Angle operator+(const Angle& rhs)
    {
        Angle ret;

        ret.m_angle = m_angle + rhs.m_angle;
        return ret;
    }

    const Angle& operator+=(const Angle& rhs)
    {
        m_angle += rhs.m_angle;
        return *this;
    }

    const Angle operator-(const Angle& rhs)
    {
        Angle ret;

        ret.m_angle = m_angle - rhs.m_angle;
        return ret;
    }

    const Angle& operator-=(const Angle& rhs)
    {
        m_angle -= rhs.m_angle;
        return *this;
    }

private:
    float m_angle { 0.0f };
};