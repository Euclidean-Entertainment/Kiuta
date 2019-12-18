/**
 * 
 */
#pragma once

#include <cstdio>
#include <cmath>
#include <GL/gl.h>
#include "common/assert.h"

class Vec2
{
public:
    Vec2() {}
    Vec2(GLfloat x, GLfloat y) : m_x(x), m_y(y) {}

    const GLfloat magnitude() const { return sqrt((m_x * m_x) + (m_y * m_y)); }

    const GLfloat angle() 
    { 
        ASSERT(m_x != 0);
        return atan(m_y / m_x);
    }

    const GLfloat x() { return m_x; }
    const GLfloat y() { return m_y; }

    Vec2 operator+(const Vec2& rhs)
    {
        return Vec2(m_x + rhs.m_x, m_y + rhs.m_y);
    }

    Vec2 operator-(const Vec2& rhs)
    {
        return Vec2(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    Vec2 operator*(const GLfloat scalar)
    {
        return Vec2(m_x * scalar, m_y * scalar);
    }

    Vec2 operator/(const GLfloat scalar)
    {
        ASSERT(scalar != 0);
        return Vec2(m_x / scalar, m_y / scalar);
    }


    Vec2& operator+=(const Vec2& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        return *this;
    }

    Vec2& operator-=(const Vec2& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        return *this;
    }

    Vec2& operator*=(const GLfloat scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        return *this;    
    }

    Vec2& operator/=(const GLfloat scalar)
    {
        ASSERT(scalar != 0);

        m_x /= scalar;
        m_y /= scalar;
        return *this;
    }

    GLfloat dot(const Vec2& b) const
    {
        return m_x * b.m_x + m_y * b.m_y;
    }

    void print() const 
    {
        std::printf("[%.4f %.4f]\n", m_x, m_y);
    }

private:
    GLfloat m_x;
    GLfloat m_y;
};