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
 * Creation Date: 24/12/19
 * Author: Jesse Buhagiar
 * Last Modified:
 * Modified By: Jesse Buhagiar (jooster669@gmail.com>)
 * Copyright (c) 2019 Euclidean Entertainment
 * 
 * History:
 * 
 */
#pragma once

#include "gl/texture.h"

class CBackgroundTexture : public CTexture
{
public:
    CBackgroundTexture() : CTexture(){ log(LogLevel::INFO, "CBackgroundTexture: created a new background image\n"); }
    ~CBackgroundTexture(){}

    void bind() const override;
    void unbind() const override;
    void upload(const CMSBitmap& bitmap) const override;
    
private:

};