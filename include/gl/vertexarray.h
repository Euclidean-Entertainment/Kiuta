/**
 * 
 */
#pragma once

#include "gl/buffer.h"

#include <GL/glew.h>
#include <string>
#include <vector>

/**
 *  Vertex Attribute structure
 */
struct VertexAttribute
{
    /**
     * Enum types for each component in the vertex buffer for attribute n
     */
    enum AttributeType : GLenum
    {
        BYTE = GL_BYTE,
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        SHORT = GL_SHORT,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        INT = GL_INT,
        UNSIGNED_INT = GL_UNSIGNED_INT,

        HALF_FLOAT = GL_HALF_FLOAT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE,
        FIXED_POINT = GL_FIXED,
        INT_2_10_10_10 = GL_INT_2_10_10_10_REV,
        UNSIGNED_INT_2_10_10_10 = GL_UNSIGNED_INT_2_10_10_10_REV,
        UNSIGNED_INT_10F_11F_11F = GL_UNSIGNED_INT_10F_11F_11F_REV
    };

    GLuint idx;          /**< Which index this attribute is mapped to via layout(location = ) in the vertex stage of the pipeline */
    GLint size;          /**< Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4 */
    GLboolean normalize; /**< Should the data for this attribute be normalized by the GPU? */
    GLsizei stride;      /**< Byte offset between attributes. That is, is we have memory layout of {vertex, normal, colour}, each of 8-bits, the stride would be 2 [bytes] */
    GLintptr offset;     /**< Data offset for first element */
};

/**
 * OpenGL Vertex Array Object wrapper class. See this file's header for more information on what a VAO is.
 * This VAO is mostly just used to map bindings for buffers (say for a mesh). There are
 * other uses, however for our intents, that will be MORE than enough.
 *
 * This class doesn't really need to store any data per se; mostly just the VAO object ID
 * and name/other forms of metadata.
 *
 * @note This class <i>CANNOT</i> be inherited from!
 *
 */
class CGLVertexArray final
{
public:
    static constexpr GLuint VAO_UNBIND = 0;

public:
    CGLVertexArray();
    CGLVertexArray(const CGLVertexArray& rhs);
    ~CGLVertexArray() { glDeleteVertexArrays(1, &m_vao); }

    void set_name(const std::string& name) { m_name = name; }

    void bind() const;
    void unbind() const;

    GLuint vao() const { return m_vao; }
    const std::string& name() const { return m_name; }

    template<typename T, GLenum gl_type>
    int attach_buffer(const CGLBuffer<T, gl_type>&);

    template<typename T, GLenum gl_type>
    int attach_buffer(int, CGLBuffer<T, gl_type>&);

private:
    GLuint m_vao { 0 };
    std::string m_name {};
};
