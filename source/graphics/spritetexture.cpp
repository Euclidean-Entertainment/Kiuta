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
#include "gl/spritetexture.h"

void CSpriteTexture::bind() const
{
    log(LogLevel::INFO, "CSpriteTexture: binding texture %s(%ld) to GL_TEXTURE_2D\n", name().c_str(), texture_id());
    glBindTexture(GL_TEXTURE_2D, texture_id());
}

void CSpriteTexture::unbind() const
{
    log(LogLevel::INFO, "CSpriteTexture: unbinding texture %s(%ld)\n", name().c_str(), texture_id());
    glBindTexture(GL_TEXTURE_2D, CTexture::TEXTURE_RESET);
}