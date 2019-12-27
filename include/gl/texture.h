/*
 * Kisetsu No Uta
 * Copyright (C) 2019 Euclidean Entertainment
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of,
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * 
 * Creation Date: 21/12/19
 * Author: Jesse Buhagiar
 * Last Modified:
 * Modified By: Jesse Buhagiar (jooster669@gmail.com>)
 * Copyright (c) 2019 Euclidean Entertainment
 * 
 * History:
 * 
 */
#pragma once

#include "loader/bitmap.h"
#include "common/die.h"

#include <GL/gl.h>
#include <string>
#include <vector>

/**
 * Texture base class. 
 * 
 * All texture types (such as a normal/bump map) etc inherit off of this class. 
 * This makes it much more managable to handle textures, as we can simply have a 
 * nice container of type `CTexture` and iterate over that. 
 * 
 */
class CTexture
{
public:
    /**
     * We only support two types of color format
     */
    enum class ColorFormat : GLenum
    {
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    enum class DataType : GLenum
    {
        BYTE = GL_BYTE,
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        SHORT = GL_SHORT,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT
    };

    enum class Target : GLenum
    {
        TEXTURE_2D = GL_TEXTURE_2D
    };

    static constexpr GLuint TEXTURE_RESET = 0;

protected:
    CTexture()
    : m_bound(false), m_texid(0), m_name("DEFAULT"), m_format(ColorFormat::RGB), m_type(DataType::UNSIGNED_BYTE) { glGenTextures(1, &m_texid); }

    CTexture(const std::string& name)
    : m_bound(false), m_texid(0), m_name(name), m_format(ColorFormat::RGB), m_type(DataType::UNSIGNED_BYTE) { glGenTextures(1, &m_texid); }

    virtual ~CTexture() { glDeleteTextures(1, &m_texid); }

    virtual void bind() const { die("Whoa! How did CTexture::bind() get called!?!?!\n"); }
    virtual void unbind() const { die("Whoa! How did CTexture::unbind() get called!?!?!\n"); };

    template<typename T>
    void set_parameter(GLenum pname, T param);
    
    virtual void upload(__attribute__((unused)) const CMSBitmap& bitmap) const { die("Whoa! How did CTexture::upload() get called!?!?!\n"); };

    const ColorFormat& format() const { return m_format; }
    const DataType& internal_type() const { return m_type; }
    const std::string& name() const { return m_name; }
    GLuint texture_id() const { return m_texid; }

private:
    bool m_bound;
    GLuint m_texid;
    std::string m_name;

    ColorFormat m_format;
    DataType m_type;
};