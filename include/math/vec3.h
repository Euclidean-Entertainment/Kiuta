/**
 * 
 */
#pragma once

#include <cmath>
#include <cstdio>
#include <GL/gl.h>
#include "common/assert.h"

class Vec3
{
public:
    Vec3() {}
    Vec3(GLfloat x, GLfloat y, GLfloat z) : m_x(x), m_y(y), m_z(z) {}
    Vec3(const GLfloat data[3]) : m_x(data[0]), m_y(data[1]), m_z(data[2]) {}

    GLfloat magnitude() const { return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z)); }

    GLfloat angle() 
    { 
        ASSERT(m_x);
        return atan(m_y / m_x);
    }

    GLfloat x() const { return m_x; }
    GLfloat y() const { return m_y; }
    GLfloat z() const { return m_z; }
    const GLfloat* poisition() 
    {
        m_array[0] = m_x;
        m_array[1] = m_y;
        m_array[2] = m_z;

        return m_array;
    }

    Vec3 operator+(const Vec3& rhs)
    {
        return Vec3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
    }

    Vec3 operator-(const Vec3& rhs)
    {
        return Vec3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
    }

    Vec3 operator*(const GLfloat scalar)
    {
        return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
    }

    Vec3 operator/(const GLfloat scalar)
    {
        ASSERT(scalar);
        return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        m_z += rhs.m_z;
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        m_z -= rhs.m_z;
        return *this;
    }

    Vec3& operator*=(const GLfloat scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        return *this;    
    }

    Vec3& operator/=(const GLfloat scalar)
    {
        ASSERT(scalar);

        m_x /= scalar;
        m_y /= scalar;
        m_z /= scalar;
        return *this;
    }

    GLfloat dot(const Vec3& b) const
    { 
        return m_x * b.m_x + m_y * b.m_y + m_z * b.m_z; 
    }
    
    Vec3 cross(const Vec3& b) const
    {
        return Vec3((m_y * b.m_z) - (m_z * b.m_y), (m_z * b.m_x) - (m_x * b.m_z), (m_x * b.m_y) - (m_y * b.m_x));
    }

    void print() const
    {
        std::printf("[%.4f %.4f %.4f]\n", m_x, m_y, m_z);
    }

private:
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_z;
    GLfloat m_array[3];
};