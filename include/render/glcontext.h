/**
 *
 */
#pragma once

#include <string>
#include <vector>


#include <SDL2/SDL.h>
#include <GL/glew.h>

class CWindow; 

class CGLContext final
{
public:
    explicit CGLContext(){}

    void create(const CWindow& hwnd);
    void get_extensions();

    const std::string& vendor() const { return m_vendor; }
    const std::string& version() const { return m_version; }
    const std::string& driver() const {return m_driver; }

private:
    static const char* GLGetString(GLenum name);

private:
    std::string m_vendor;
    std::string m_version;
    std::string m_driver;
    std::vector<const char*> m_extensions;
};