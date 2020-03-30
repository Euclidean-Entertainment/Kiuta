/**
 * 
 */
#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include "common/log.hpp"

template<typename T>
class CResourceManager
{
public:
    void add(uint32_t&& key, T&& object)
    {
        log(LogLevel::INFO, "CResourceManager<%s>: Adding object to list at key %ld\n", typeid(T).name(), key);
        m_resources.insert(std::make_pair<uint32_t, T>(std::move(key), std::move(object)));
    }

    const T& get(uint32_t key)
    {
        auto& elem = m_resources.find(key);
        if(elem == m_resources.end())
        {
            log(LogLevel::WARN, "CResourceManager<%s>: Unable to find resource at key %ld\n", typeid(T).name(), key);
            return m_resources.end();
        }

        return elem->second();
    }

    size_t size()
    {
        return m_resources.size();
    }

    void flush()
    {
        m_resources.clear();
    }

private:
    std::unordered_map<uint32_t, T> m_resources;
};