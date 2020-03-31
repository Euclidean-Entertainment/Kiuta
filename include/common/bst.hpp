/**
 * Binary search tree
 */
#pragma once

#define BST_DEBUG

#include <utility>

namespace LibCommon
{

template<class T>
class CBST final
{
    struct Node
    {
        explicit Node(const T& _data)
        : left(nullptr), right(nullptr), data(_data) {}
        explicit Node(T&& _data)
        : left(nullptr), right(nullptr), data(std::move(_data)) {}
        Node* left;
        Node* right;
        T data;
    };

public:
    CBST() {}
    ~CBST() {}

    void insert(const T& data)
    {
        Node* new_node = new Node(data);

        if(m_root == nullptr)
        {
            m_root = new_node;
            return;
        }

        Node* node = m_root;
        while(true)
        {
            if(data <= node->data)
            {
                if(node->left == nullptr)
                {
                    node->left = new_node;
                    return;
                }
                else
                {
                    node = node->left;
                    continue;
                }
            }
            else if(data >= node->data)
            {
                if(node->right == nullptr)
                {
                    node->right = new_node;
                    return;
                }
                else
                {
                    node = node->right;
                    continue;
                }
            }
        }
    }

    void insert(T&& data)
    {
        Node* new_node = new Node(data);

        if(m_root == nullptr)
        {
            m_root = new_node;
            return;
        }

        Node* node = m_root;
        while(true)
        {
            if(data <= node->data)
            {
                if(node->left == nullptr)
                {
                    node->left = new_node;
                    return;
                }
                else
                {
                    node = node->left;
                    continue;
                }
            }
            else if(data >= node->data)
            {
                if(node->right == nullptr)
                {
                    node->right = new_node;
                    return;
                }
                else
                {
                    node = node->right;
                    continue;
                }
            }
        }
    }

    void remove(const T& key)
    {
    }

    void remove(T&& key)
    {
    }

    T& find(const T& key, Node* node = root_node())
    {
        if(node == nullptr || node->data == key)
            return node->data;

        if(key < node->data)
            return find(key, node->left);

        return find(key, node->right);
    }

    const Node* root_node() const { return m_root(); }
    T& root_value() const { return m_root->data; }

private:
    Node* m_root { nullptr };
};
} // namespace LibCommon