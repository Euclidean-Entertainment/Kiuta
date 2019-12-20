/**
 * 
 */
#include "render/renderer.h"
#include "common/log.hpp"

#include <glm/gtc/matrix_transform.hpp>

CRenderer::CRenderer(int width, int height) : m_width(width), m_height(height), m_projection()
{
    log(LogLevel::INFO, "CRenderer: created a renderer with w = %d, h = %d\n", m_width, m_height);
    m_projection = glm::ortho(0, m_width, m_height, 0);
}

CRenderer::CRenderer(const CWindow& hwnd) : m_width(hwnd.dimensions().width()), m_height(hwnd.dimensions().height()), m_projection()
{
    log(LogLevel::INFO, "CRenderer: created a renderer with w = %d, h = %d\n", m_width, m_height);
    m_projection = glm::ortho(0, m_width, m_height, 0);
}