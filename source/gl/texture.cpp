/**
 * 
 */

#include "gl/texture.h"

#include "common/log.hpp"

CTexture::CTexture()
: m_texid(0), m_target(0), m_internal_format(0), m_format(0), m_type(GL_UNSIGNED_BYTE), m_width(0), m_height(0)
{
    glGenTextures(1, &m_texid);
    glBindTexture(GL_TEXTURE_2D, m_texid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, TEXTURE_RESET);
}

CTexture::CTexture(GLenum target)
: m_texid(0), m_target(target), m_internal_format(0), m_format(0), m_type(GL_UNSIGNED_BYTE), m_width(0), m_height(0)
{
    glGenTextures(1, &m_texid);

    glBindTexture(target, m_texid);

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(target, TEXTURE_RESET);
}

CTexture::CTexture(GLenum target, GLint internal_format)
: m_texid(0), m_target(target), m_internal_format(internal_format), m_format(0), m_type(GL_UNSIGNED_BYTE), m_width(0), m_height(0)
{
    glGenTextures(1, &m_texid);
}

CTexture::CTexture(GLenum target, GLint internal_format, GLenum format, GLenum type)
: m_texid(0), m_target(target), m_internal_format(internal_format), m_format(format), m_type(type), m_width(0), m_height(0)
{
    glGenTextures(1, &m_texid);
}

CTexture::~CTexture()
{
    glDeleteTextures(1, &m_texid);
}

void CTexture::create_empty(GLsizei width, GLsizei height)
{
#ifdef DEBUG
    log(LogLevel::INFO, "CTexture: creating empty texture [default] of size %ldx%ld\n", width, height);
#endif
    glBindTexture(GL_TEXTURE_2D, m_texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_RESET);

    m_width = width;
    m_height = height;
}

void CTexture::create_empty(GLenum target, GLint internal_format, GLenum format, GLenum type, GLsizei width, GLsizei height)
{
#ifdef DEBUG
    log(LogLevel::INFO, "CTexture: creating empty texture of size %ldx%ld\n", width, height);
#endif
    glBindTexture(target, m_texid);
    glTexImage2D(target, 0, internal_format, width, height, 0, format, type, 0);
    glBindTexture(target, TEXTURE_RESET);
}

void CTexture::bind() const
{
    glBindTexture(m_target, m_texid);
}

void CTexture::bind(GLenum tex_unit) const
{
    ASSERT(tex_unit >= GL_TEXTURE0);
    glActiveTexture(tex_unit);
    glBindTexture(m_target, m_texid);
}

void CTexture::bind(GLenum target, GLenum tex_unit) const
{
    ASSERT(tex_unit >= GL_TEXTURE0);
    glActiveTexture(tex_unit);
    glBindTexture(target, m_texid);
}

void CTexture::unbind() const
{
    glBindTexture(m_target, TEXTURE_RESET);
}

void CTexture::unbind(GLenum target) const
{
    glBindTexture(target, TEXTURE_RESET);
}

void CTexture::upload(TextureType img_type, const std::string& path)
{
#ifdef DEBUG
    log(LogLevel::INFO, "CTexture: uploading %s to Texture Memory\n", path.c_str());
#endif
    glBindTexture(m_target, m_texid);

    // This is an if/else ladder because switch/case doesn't work
    // with initialization of an object!
    if(img_type == TextureType::MS_BITMAP)
    {
        CMSBitmap bitmap(path);
        glTexImage2D(m_target, 0, m_internal_format, bitmap.width(), bitmap.height(), 0, m_format, m_type, bitmap.pixel_data());
    }
    else if(img_type == TextureType::TARGA)
    {
        log(LogLevel::WARN, "CTexture: TGA not implemented! Come back later!\n");
    }
    else
    {
        log(LogLevel::WARN, "CTexture: Unknown texture format, %ld\n", img_type);
    }

    glBindTexture(m_target, TEXTURE_RESET);
}

void CTexture::upload(GLenum target, GLint internal_format, GLenum format, GLenum type, TextureType img_type, const std::string& path) const
{
#ifdef DEBUG
    log(LogLevel::INFO, "CTexture: uploading %s to Texture Memory\n", path.c_str());
#endif
    glBindTexture(target, m_texid);
    if(img_type == TextureType::MS_BITMAP)
    {
        CMSBitmap bitmap(path);
        glTexImage2D(target, 0, internal_format, bitmap.width(), bitmap.height(), 0, format, type, bitmap.pixel_data());
    }
    else if(img_type == TextureType::TARGA)
    {
        log(LogLevel::WARN, "CTexture: TGA not implemented! Come back later!\n");
    }
    else
    {
        log(LogLevel::WARN, "CTexture: Unknown texture format, %ld\n", type);
    }

    glBindTexture(target, TEXTURE_RESET);
}

void CTexture::upload(const CMSBitmap& bitmap) const
{
    glBindTexture(m_target, m_texid);
    glTexImage2D(m_target, 0, m_internal_format, bitmap.width(), bitmap.height(), 0, m_format, m_type, bitmap.pixel_data());
    glBindTexture(1, TEXTURE_RESET);
}

void CTexture::upload(GLenum target, GLint internal_format, GLenum format, GLenum type, const CMSBitmap& bitmap) const
{
    glBindTexture(target, m_texid);
    glTexImage2D(target, 0, internal_format, bitmap.width(), bitmap.height(), 0, format, type, bitmap.pixel_data());
    glBindTexture(target, TEXTURE_RESET);
}

template<>
void CTexture::set_parameter<GLint>(GLenum target, GLenum pname, GLint param) const
{
    glBindTexture(target, m_texid);
    glTexParameterf(target, pname, param);
    glBindTexture(target, TEXTURE_RESET);
}

template<>
void CTexture::set_parameter<GLfloat>(GLenum target, GLenum pname, GLfloat param) const
{
    glBindTexture(target, m_texid);
    glTexParameterf(target, pname, param);
    glBindTexture(target, TEXTURE_RESET);
}

template<>
void CTexture::set_parameter<GLint>(GLenum pname, GLint param) const
{
    glBindTexture(m_target, m_texid);
    glTexParameterf(m_target, pname, param);
    glBindTexture(m_target, TEXTURE_RESET);
}

template<>
void CTexture::set_parameter<GLfloat>(GLenum pname, GLfloat param) const
{
    glBindTexture(m_target, m_texid);
    glTexParameterf(m_target, pname, param);
    glBindTexture(m_target, TEXTURE_RESET);
}