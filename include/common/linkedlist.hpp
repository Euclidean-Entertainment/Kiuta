/**
 * Singly linked list
 */
#pragma once

//#define LL_DEBUG

#include "common/assert.h"
#include <cstdio>
#include <utility>

namespace LibCommon
{

template <class T>
class CLinkedList final
{
    struct Node
    {
        explicit Node(const T& _data) : data(_data){}
        explicit Node(T&& _data) : data(std::move(_data)){}
        T data;
        Node* next { nullptr };
    };

public:
    CLinkedList(){}
    ~CLinkedList(){}

    void insert(const T& data)
    {
        Node node = new Node(data);
    #ifdef LL_DEBUG
        printf("inserting a new node @ %p!\n", node);
    #endif
        if(!m_head)
        {
            m_head = node;
            m_tail = m_head;
            return;
        }

        m_tail->next = node;
        m_tail = node;
        m_count++;
    }

    void insert(T&& data)
    {
        Node* node = new Node(data);
    #ifdef LL_DEBUG
        printf("inserting a new node @ %p!\n", node);
    #endif
        if(!m_head)
        {
            m_head = node;
            m_tail = m_head;
            return;
        }

        m_tail->next = node;
        m_tail = node;
        m_count++;
    }


    void remove(const T& data)
    {
        ASSERT(m_count != 0);
    }

    void remove(T&& data)
    {
        ASSERT(m_count != 0);
        Node* prev;
        for(Node* node = m_head; node != nullptr;)
        {
            if(node->data == data)
            {
                if(node == m_head)
                {
                    m_head = m_head->next;
                }
                else if(node == m_tail)
                {
                    m_tail = prev;
                    m_tail->next = nullptr;
                }
                else
                {
                    prev->next = node->next;
                }
                
            #ifdef LL_DEBUG
                printf("removing a node @ %p!\n", node);
            #endif  
                delete node;
                node = nullptr;
                return;
            }

            prev = node;
            node = node->next;
        }
    }

    void print() const
    {
        for(Node* node = m_head; node != nullptr;)
        {
            printf("node: %d\n", node->data);
            node = node->next;
        }

        printf("\n\n");
    }

    T first()
    {
        ASSERT(m_head != nullptr);
        Node* head = m_head;
        T ret = std::move(m_head->data);

        m_head = m_head->next;
        delete head;
        head = nullptr;

        return ret;
    }

    const T& peek_first() const { return m_head->data; }
    const T& peek_last() const { return m_tail->data; }

    const int& get_count() const { return m_count; }

private:
    Node* m_head { nullptr };
    Node* m_tail { nullptr };
    int m_count { 0 };

};

}