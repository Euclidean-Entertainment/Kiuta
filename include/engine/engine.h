/**
 * 
 */
#pragma once

#include "system/window.h"

class CEngine final
{
public:
    CEngine() = delete;
    CEngine(int, char**);

    void init();

    bool running() const { return m_running; }

private:
    void handle_cmd_arguments(int, char**);
    void main_loop();

private:
    CWindow m_hwnd;
    bool m_running { false };
};