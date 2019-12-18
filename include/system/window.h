/**
 * 
 */
#pragma once

#include "common/rect.hpp"
#include "render/glcontext.h"

#include <string>
#include <memory>
#include <SDL2/SDL.h>

/**
 * OpenGL Window
 */
class CWindow final
{
    static constexpr int default_width = 1024;
    static constexpr int default_height = 768;

    struct SDL_Destroyer
    {
        void operator()(SDL_Window* hwnd) { SDL_DestroyWindow(hwnd); }
    };

public:
    CWindow(){}
    CWindow(const CRect& rect) : m_dimensions(rect){}
    CWindow(int width, int height) : m_dimensions(CRect(width, height)){}

    void init();
    void resize(int width, int height);
    void resize(const CRect& rect);
    
    void set_fullscreen();
    void set_windowed();

    bool is_fullscreen() const { return m_fullscreen; }

    const CRect& dimensions() const { return m_dimensions; }
    const SDL_Window* hwnd() const { return m_hwnd.get(); }
    const CGLContext& context() const { return m_context; }

private:
    CRect m_dimensions { default_width, default_height };
    bool m_fullscreen { false };
    std::unique_ptr<SDL_Window, SDL_Destroyer> m_hwnd { nullptr };
    CGLContext m_context;
};