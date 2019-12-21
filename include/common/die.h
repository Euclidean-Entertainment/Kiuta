/**
 * 
 */
#pragma once

#include "common/log.hpp"

#include <SDL2/SDL_messagebox.h>
#include <cstdarg>
#include <cstdlib>
#include <execinfo.h>
#include <unistd.h>

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
    fprintf(stderr, "\n\nSTACK TRACE:\n");
    //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR", buff, nullptr);

    #ifdef __linux__
        void* bt_array[256];
        size_t size = backtrace(bt_array, 256);
        backtrace_symbols_fd(bt_array, size, STDERR_FILENO);
    #endif

    exit(SH2_DIE);
}