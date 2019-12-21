/**
 * 
 */
#include "engine/engine.h"

#include "common/die.h"

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

void CEngine::main_loop()
{
    SDL_Event event;

    while(m_running)
    {
        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT)
            break; // TODO: Send the state a message
        else if(event.type == SDL_WINDOWEVENT)
            //m_hwnd.handle_event(&event);

            glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(const_cast<SDL_Window*>(m_hwnd.hwnd()));
    }
}