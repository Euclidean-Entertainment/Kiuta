/**
 * 
 */
#pragma once

#include "loader/bitmap.h"

#include <vector>

class CSpriteSheet
{
public:
    CSpriteSheet() {}
    CSpriteSheet(const std::string&, int, int);
    CSpriteSheet(const std::string&, const std::string&, int, int);

    void load(const std::string&);
    std::vector<uint8_t> cut(int, int); // TODO: Should this return a CSprite instead???

private:
    std::string m_name;

    int m_sprite_width;
    int m_sprite_height;

    CMSBitmap m_sheet;
};