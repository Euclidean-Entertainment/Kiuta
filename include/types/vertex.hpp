/**
 * 
 */
#pragma once

#include <GL/gl.h>

struct Vertex
{
    //Position
    GLfloat x { 0.0f };
    GLfloat y { 0.0f };

    // Texture co-ordinates
    GLfloat u { 0.0f };
    GLfloat v { 0.0f};
};