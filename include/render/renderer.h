/**
 * 
 */
#pragma once

#include "system/window.h"

#include <glm/glm.hpp>

class CRenderer final
{
public:
    CRenderer() = delete; // No default constructor!
    CRenderer(int, int);
    CRenderer(const CWindow&);

    const glm::mat4& projection_matrix() const { return m_projection; }

private:
    int m_width;
    int m_height;
    glm::mat4 m_projection;
};