/**
 * 
 */
#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

/**
 * Backend buffer to store data
 */
template<typename T, GLenum gl_type>
class GLDataBuffer final
{
public:
    void fill(const T* data)
    {
        for(size_t i = 0; i < sizeof(data); i++)
            m_data.push_back(data[i]);
    }

    const void* data() const { return &m_data[0]; }
    size_t elem_size() const { return m_data_size; }
    size_t size() const { return m_data.size(); }
    GLenum type() const { return m_type; };

private:
    std::vector<T> m_data;
    size_t m_data_size { sizeof(T) };
    GLenum m_type { gl_type };
};

/**
 * Buffer binding target enum
 *
 * Specifies the target to which the buffer object is bound for glBufferData.
 */
enum BufferTarget : GLenum
{
    ARRAY_BUFFER = GL_ARRAY_BUFFER,                    /**< For Vertex Attributes */
    ATOMIC_COUNTER = GL_ATOMIC_COUNTER_BUFFER,         /**< Atomic counter Storage */
    COPY_READ = GL_COPY_READ_BUFFER,                   /**< Buffer copy source */
    COPY_WRITE = GL_COPY_WRITE_BUFFER,                 /**< Buffer copy destination */
    ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,           /**< Vertex array indices */
    PIXEL_PACK = GL_PIXEL_PACK_BUFFER,                 /**< Pixel Read target */
    PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER,             /**< Texture data source */
    QUERY = GL_QUERY_BUFFER,                           /**< Query Result Buffer */
    SHADER_STORAGE = GL_SHADER_STORAGE_BUFFER,         /**< Read-write storage for shaders */
    TEXTURE = GL_TEXTURE_BUFFER,                       /**< Texture data buffer */
    TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER, /**< Transform feedback buffer */
    UNIFORM_BUFFER = GL_UNIFORM_BUFFER                 /**< Uniform block storage */
};

/**
 * Buffer usage target enum
 *
 * "usage is a hint to the GL implementation as to how a buffer object's data store will be accessed.
 * This enables the GL implementation to make more intelligent decisions that may significantly impact
 * buffer object performance. It does not, however, constrain the actual usage of the data store.
 * usage can be broken down into two parts: first, the frequency of access (modification and usage),
 * and second, the nature of that access."
 */
enum BufferUsage : GLenum
{
    /**
     *  Draw usage
     *
     *  The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
     */
    STREAM_DRAW = GL_STREAM_DRAW,   /**< The data store contents will be modified once and used at most a few times */
    STATIC_DRAW = GL_STATIC_DRAW,   /**< The data store contents wil be modified once and used many times */
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW, /**< The data store contents will be modified repeatedly and used many times */

    /**
     * Read usage
     *
     * The data store contents are modified by reading data from the GL, and used as the source for
     * GL drawing and image specification commands.
     */
    STREAM_READ = GL_STREAM_READ,   /**< The data store contents will be modified once and used at most a few times */
    STATIC_READ = GL_STATIC_READ,   /**< The data store contents wil be modified once and used many times */
    DYNAMIC_READ = GL_DYNAMIC_READ, /**< The data store contents will be modified repeatedly and used many times */

    /**
     * Copy usage
     *
     * The data store contents are modified by reading data from the GL, and used to return that data when queried by the application
     */
    STREAM_COPY = GL_STREAM_COPY,   /**< The data store contents will be modified once and used at most a few times */
    STATIC_COPY = GL_STATIC_COPY,   /**< The data store contents wil be modified once and used many times */
    DYNAMIC_COPY = GL_DYNAMIC_COPY, /**< The data store contents will be modified repeatedly and used many times */
};

template<typename T, GLenum gl_type>
class CGLBuffer final
{
public:
    static constexpr GLuint VBO_RESET = 0; /**< ""Reset"" VBO ID */

public:
    CGLBuffer();
    CGLBuffer(const char*);
    CGLBuffer(const CGLBuffer&);
    ~CGLBuffer();

    void set_name(const std::string& name) { m_name = name; }

    GLuint buffer_object() const { return m_buffer_object; }
    BufferTarget target() const { return m_target; }

    void buffer_data(BufferTarget, GLsizeiptr size, const void* data, BufferUsage, int num_components);

    const CGLBuffer& operator=(const CGLBuffer& rhs);
    const char* name() const { return m_name.c_str(); }

    const void* data() const { return &m_data[0]; }
    size_t type_size() const { return m_data_size; }
    int num_components() const { return m_num_components; } // NOTE: This gets number of elems per object (i.e, a vec3 would be size 3)
    size_t size() const { return m_data.size(); }
    GLenum type() const { return m_type; };

    void bind() const { glBindBuffer(m_target, m_buffer_object); }
    void unbind() const { glBindBuffer(m_target, 0); }

private:
    // Fill this buffer with data (on the CPU side)
    // FIXME: This could probably be turned when we don't need to debug!?!?
    void fill(const T* data)
    {
        for(size_t i = 0; i < sizeof(data); i++)
            m_data.push_back(data[i]);
    }

private:
    GLuint m_buffer_object { 0 };
    std::string m_name { " " };
    BufferTarget m_target { BufferTarget::ARRAY_BUFFER };
    int m_num_components { 0 };

    std::vector<T> m_data;
    size_t m_data_size { sizeof(T) };
    GLenum m_type { gl_type };
};
