/**
 * 
 */
#include "common/log.hpp"
#include "gl/buffer.h"
#include "common/assert.h"

template<typename T, GLenum gl_type>
CGLBuffer<T, gl_type>::CGLBuffer()
{
    glGenBuffers(1, &m_buffer_object);
#ifdef DEBUG
    log(LogLevel::INFO, "CGLBuffer: created buffer %u\n", m_buffer_object);
#endif
}

template<typename T, GLenum gl_type>
CGLBuffer<T, gl_type>::CGLBuffer(const char* name)
{
    glGenBuffers(1, &m_buffer_object);
    m_name = name;
#ifdef DEBUG
    log(LogLevel::INFO, "CGLBuffer: created buffer \"%s\"(%u)\n", name, m_buffer_object);
#endif
}

template<typename T, GLenum gl_type>
CGLBuffer<T, gl_type>::CGLBuffer(const CGLBuffer& rhs)
{
    m_buffer_object = rhs.m_buffer_object;
    m_name = rhs.m_name;
    m_target = rhs.m_target;

    m_data = rhs.m_data;
    m_data_size = rhs.m_data_size;
    m_type = rhs.m_type;
}

template<typename T, GLenum gl_type>
CGLBuffer<T, gl_type>::~CGLBuffer()
{
#ifdef DEBUG
    log(LogLevel::INFO, "CGLBuffer: deleting buffer %u\n", m_buffer_object);
#endif
    glDeleteBuffers(1, &m_buffer_object);
}

template<typename T, GLenum gl_type>
void CGLBuffer<T, gl_type>::buffer_data(BufferTarget target, GLsizeiptr size, const void* data, BufferUsage usage, int num_components)
{
    ASSERT(m_buffer_object);
    ASSERT(data != nullptr);

#ifdef DEBUG
    log(LogLevel::INFO, "CGLBuffer: filling buffer of size %ld with data at %p\n", size, data);
    fill(reinterpret_cast<const T*>(data)); // This just wastes time and space on a non-debug build! That and we can always use a GL Debugger tbh
#endif
    m_num_components = num_components;
    m_target = target;

    glBindBuffer(target, m_buffer_object);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
}

template class CGLBuffer<float, GL_FLOAT>;
template class CGLBuffer<int, GL_INT>;
template class CGLBuffer<uint16_t, GL_UNSIGNED_SHORT>;