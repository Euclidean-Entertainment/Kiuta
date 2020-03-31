/**
 * 
 */
#include "engine/engine.h"

#include "common/die.h"
#include "gl/buffer.h"
#include "gl/shader.h"
#include "gl/vertexarray.h"
#include "render/renderer.h"
#include "types/vertex.hpp"

CEngine::CEngine(int argc, char** argv)
{
}

void CEngine::init()
{
    // Let's initialise SDL2
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        die("Failed to initialise SDL2!\n");

    m_hwnd.init();
    m_running = true;
    main_loop();
}

Vertex data[] = {
    { -1.0f, 1.0f,
      0.0f, 1.0f },
    { -1.0f, -1.0f,
      0.0f, 0.0f },
    { 1.0f, -1.0f,
      1.0f, 0.0f }
};

void CEngine::main_loop()
{
    SDL_Event event;
    CShader shader;

    CGLVertexArray vao;
    CGLBuffer<GLfloat, GL_FLOAT> vbo;

    vao.bind();
    vbo.buffer_data(BufferTarget::ARRAY_BUFFER, sizeof(data), reinterpret_cast<void*>(&data), BufferUsage::STATIC_DRAW, 2);
    vao.attach_buffer_to_attribute(0, 2, vbo, 4 * sizeof(GLfloat), nullptr);
    vao.attach_buffer_to_attribute(1, 2, vbo, 4 * sizeof(GLfloat), reinterpret_cast<void*>(offsetof(Vertex, Vertex::u)));
    vao.unbind();

    shader.load("test");
    while(m_running)
    {
        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT)
            break; // TODO: Send the state a message
        else if(event.type == SDL_WINDOWEVENT)
            //m_hwnd.handle_event(&event);

            glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        shader.bind();
        shader.set_uniform("tex", 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(const_cast<SDL_Window*>(m_hwnd.hwnd()));
    }
}