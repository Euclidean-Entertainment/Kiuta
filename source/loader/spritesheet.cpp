/**
 * 
 */
#include "loader/spritesheet.h"

#include "common/log.hpp"

#include <cstring>

CSpriteSheet::CSpriteSheet(const std::string& name, int width, int height)
: m_name(name), m_sprite_width(width), m_sprite_height(height)
{
}

CSpriteSheet::CSpriteSheet(const std::string& name, const std::string& fname, int width, int height)
: m_name(name), m_sprite_width(width), m_sprite_height(height)
{
    load(fname);
}

void CSpriteSheet::load(const std::string& fname)
{
    log(LogLevel::INFO, "CSpriteSheet: loading spritesheet %s\n", m_name.c_str());
    m_sheet.load(fname);
}

std::vector<uint8_t> CSpriteSheet::cut(int x_origin, int y_origin)
{
    std::vector<uint8_t> ret;

    ret.resize(m_sprite_width * m_sprite_height);
    for(int y = 0; y < m_sprite_width; y++)
        memcpy(&ret.data()[y * m_sprite_width], &m_sheet.pixel_data()[(y * m_sprite_width) + x_origin], m_sprite_width);

    return ret;
}