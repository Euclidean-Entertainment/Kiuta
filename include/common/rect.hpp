/**
 * Basic rectangle
 */
#pragma once

#include <string>
#include <cstdio>

class CRect final
{
private:
    struct Rect
    {
        int width;
        int height;
    };

public:
    CRect() = delete;
    explicit CRect(int width, int height) : m_rect({width, height}){}
    explicit CRect(const CRect& rect) : m_rect(rect.m_rect){}

    void set_width(const int width) { m_rect.width = width; }
    void set_height(const int height) { m_rect.height = height; }

    int width() const { return m_rect.width; }
    int height() const { return m_rect.height; }

    const Rect& rect() const { return m_rect; }

    void print(){ std::printf("%dx%d\n", m_rect.width, m_rect.height); }

    const std::string dimensions() const 
    { 
        std::string ret = std::to_string(m_rect.width) + "x" + std::to_string(m_rect.height);
        return ret; 
    }

private:
    Rect m_rect;
};

