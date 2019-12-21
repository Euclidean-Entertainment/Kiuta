/**
 * 
 */
#include "gl/vertexarray.h"

#include "common/assert.h"
#include "common/log.hpp"

#include <utility>

CGLVertexArray::CGLVertexArray()
{
    glGenVertexArrays(1, &m_vao);
    m_name = "";
}

CGLVertexArray::CGLVertexArray(const CGLVertexArray& rhs)
{
    m_vao = rhs.m_vao;
    m_name = rhs.m_name;
}

void CGLVertexArray::bind() const
{
    glBindVertexArray(m_vao);
}

void CGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

template<>
int CGLVertexArray::attach_buffer(int index, CGLBuffer<float, GL_FLOAT>& buffer)
{
    ASSERT(m_vao);

#ifdef DEBUG
    log(LogLevel::INFO, "CGLVertexArray: attaching buffer %s to VAO!\n", buffer.name());
    log(LogLevel::INFO, "CGLVertexArray: index = %d, buffer.type_size() = %ld buffer.size() == %ld\n", index, buffer.type_size(), buffer.size());
#endif
    buffer.bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer.num_components(), buffer.type(), GL_FALSE, 0, nullptr);

    return 0;
}