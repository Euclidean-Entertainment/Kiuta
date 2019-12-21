/**
 * 
 */
#pragma once

#include "common/log.hpp"

#include <SDL2/SDL_messagebox.h>
#include <cstdarg>
#include <cstdlib>

#define SH2_DIE -1
#define BUFF_SIZE 4096

[[noreturn]] inline void die(const char* msg, ...)
{
    std::va_list va_args;
    char buff[BUFF_SIZE];

    va_start(va_args, msg);
    vsnprintf(buff, BUFF_SIZE, msg, va_args);
    va_end(va_args);

    log(LogLevel::FATAL, buff);
    //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR", buff, nullptr);
    exit(SH2_DIE);
}