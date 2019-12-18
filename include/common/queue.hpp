/**
 * FIFO queue
 */
#pragma once

#include "common/linkedlist.hpp"

namespace LibCommon
{

template <class T>
class CQueue
{
public:
    CQueue(){}
    ~CQueue(){} // FIXME: Do we need to clear out m_backend here so we don't have a leak??

    void enqueue(const T& data)
    {
        m_data.insert(data);
        m_size++;
    }

    void enqueue(T&& data)
    {
        m_data.insert(std::move(data));
        m_size++;
    }

    T dequeue()
    {
        m_size--;
        return m_data.first();
    }

    const int& size() const { return m_size; }

private:
    CLinkedList<T> m_data;
    int m_size { 0 };
};














}