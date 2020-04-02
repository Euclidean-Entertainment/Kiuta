/**
 * 
 */
#pragma once

#include "loader/bitmap.h"

#include <GL/gl.h>
#include <string>

static constexpr GLuint TEXTURE_RESET = 0;

enum TextureType
{
    MS_BITMAP,
    TARGA
};

class CTexture
{
public:
    CTexture();
    CTexture(GLenum target);
    CTexture(GLenum target, GLint internal_format);
    CTexture(GLenum target, GLint internal_format, GLenum format, GLenum type);
    ~CTexture();

    void upload(TextureType, const std::string&);
    void upload(GLenum target, GLint internal_format, GLenum format, GLenum type, TextureType, const std::string&) const;
    void upload(const CMSBitmap&) const;
    void upload(GLenum target, GLint internal_format, GLenum format, GLenum type, const CMSBitmap&) const;

    // Create an empty texture (for use with framebuffer effects)
    void create_empty(GLsizei width, GLsizei height);
    void create_empty(GLenum target, GLint internal_format, GLenum format, GLenum type, GLsizei width, GLsizei height);

    void bind() const;
    void bind(GLenum tex_unit) const;
    void bind(GLenum target, GLenum tex_unit) const;
    void unbind() const;
    void unbind(GLenum target) const;

    template<typename T>
    void set_parameter(GLenum target, GLenum pname, T param) const;

    template<typename T>
    void set_parameter(GLenum pname, T param) const;

    const GLuint& texture() const { return m_texid; }
    const size_t& width() const { return m_width; }
    const size_t& height() const { return m_height; }

private:
private:
    GLuint m_texid;          // ID of this texture, generated by OpenGL
    GLenum m_target;         // Target to bind this texture to
    GLint m_internal_format; // Number of color components in the texture
    GLenum m_format;         // Format of the pixel data
    GLenum m_type;           // Data integral type

    size_t m_width;
    size_t m_height;
};