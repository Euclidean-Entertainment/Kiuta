/**
 * 
 */
#include "system/window.h"

#include "common/assert.h"
#include "common/log.hpp"

void CWindow::init()
{
    m_hwnd.reset(SDL_CreateWindow("Kisatsu No Uta", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_dimensions.width(), m_dimensions.height(), SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL));
    m_context.create(*this);

    log(LogLevel::INFO, "Created a window of size %s\n", m_dimensions.dimensions().c_str());
}

void CWindow::set_fullscreen()
{
    ASSERT(m_hwnd.get() != nullptr);
    m_fullscreen = true;
    SDL_SetWindowFullscreen(m_hwnd.get(), SDL_WINDOW_FULLSCREEN);
}

void CWindow::set_windowed()
{
    ASSERT(m_hwnd.get() != nullptr);
    m_fullscreen = false;
    SDL_SetWindowFullscreen(m_hwnd.get(), 0);
}