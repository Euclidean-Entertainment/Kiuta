/**
 * 
 */
#include "render/glcontext.h"

#include "common/log.hpp"
#include "system/window.h"

#include <cstdio>
#include <cstdlib>
#include <limits>

static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* data)
{
    std::string errMsg;
    std::string level;

    static_cast<void>(id);
    static_cast<void>(length);
    static_cast<void>(data);

    //ASSERT(!data);
    errMsg = "";

    // Get the source of the error message
    switch(source)
    {
        case GL_DEBUG_SOURCE_API: // Error caused by the OpenGL API
            errMsg += "API ";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            errMsg += "WINDOW SYSTEM ";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            errMsg += "SHADER COMPILER ";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            errMsg += "APPLICATION ";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            errMsg += "OTHER ";
            break;
        default:
            errMsg += "UNKNOWN ";
            break;
    }

    // Get the type of error this is
    switch(type)
    {
        case GL_DEBUG_TYPE_ERROR:
            errMsg += "(ERROR): ";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            errMsg += "(DEPRECATED): ";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            errMsg += "(UNDEFINED BEHAVIOR): ";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            errMsg += "PORTABILITY! ";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            errMsg += "(PERFORMANCE): ";
            break;
        case GL_DEBUG_TYPE_OTHER:
            errMsg += "(OTHER): ";
            break;
        case GL_DEBUG_TYPE_MARKER:
            errMsg += "(MARKER): ";
            break;
        default:
            errMsg += "(UNKNOWN): ";
            break;
    }

    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            level = "[fatal]: ";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            level = "[error]: ";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            level = "[warning]: ";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            level = "[info]: ";
            break;
        default:
            level = "[info]: ";
            break;
    }

    errMsg += message;
    std::printf("%s%s\n", level.c_str(), errMsg.c_str());

    if(severity == GL_DEBUG_SEVERITY_HIGH)
        abort();
}

void CGLContext::create(const CWindow& hwnd)
{
    // We need OpenGL 4.3 for the debug callback functionality!
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Put the context into 'forwrad compatible' mode, meaning no deprecated functionality will be allowed AT ALL!
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    //ASSERT(hwnd.hwnd() != nullptr);
    SDL_GL_CreateContext(const_cast<SDL_Window*>(hwnd.hwnd()));

    int ret = 0;
    if((ret = glewInit()) != GLEW_OK)
    {
        std::string err = "CRenderContext::CRenderContext( ): GLEW Init failed! Reason: ";
        err += std::string(reinterpret_cast<const char*>(glewGetErrorString(ret)));

        std::printf("%s\n", err.c_str());
        abort();
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if(GLEW_KHR_debug)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
    else
    {
        log(LogLevel::WARN, "GL_KHR_debug not available on this OpenGL context!");
    }

    m_vendor = GLGetString(GL_VENDOR);
    m_version = GLGetString(GL_VERSION);
    m_driver = GLGetString(GL_RENDERER);

    log(LogLevel::INFO, "m_vendor:\t %s\n", m_vendor.c_str());
    log(LogLevel::INFO, "m_version:\t %s\n", m_version.c_str());
    log(LogLevel::INFO, "m_driver:\t %s\n", m_driver.c_str());
}

void CGLContext::get_extensions()
{
    GLint numExts;

    glGetIntegerv(GL_NUM_EXTENSIONS, &numExts); // Get the number of extensions the system supports

    // This generates a "-Wsign-compare" but we can ignore it
    static_assert(std::numeric_limits<GLuint>::max() >= std::numeric_limits<decltype(static_cast<GLuint>(numExts))>::max(), "GLuint must be able to represent all positive values of numExts");
    GLuint uNumExts = static_cast<GLuint>(numExts);
    m_extensions.reserve(uNumExts);

    // Iterate over each extension the graphics card supports and store it
    for(GLuint i = 0; i < uNumExts; i++)
    {
        m_extensions.push_back(reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)));
    }
}

const char* CGLContext::GLGetString(GLenum name)
{
    return reinterpret_cast<const char*>(glGetString(name));
}