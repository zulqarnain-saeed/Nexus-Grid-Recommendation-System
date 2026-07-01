#pragma once
#include <iostream>
using namespace std;
template <class T>
class AVLNode
{
public:
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
    AVLNode(T value)
    {
        data = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};
template <class T>
class AVL
{
private:
    AVLNode<T>* root;
    int bigger(int first, int second) const
    {
        if (first > second)
        {
            return first;
        }

        return second;
    }
    int nodeHeight(AVLNode<T>* node) const
    {
        if (node == NULL)
        {
            return 0;
        }

        return node->height;
    }
    int balance(AVLNode<T>* node) const
    {
        if (node == NULL)
        {
            return 0;
        }

        return nodeHeight(node->left) - nodeHeight(node->right);
    }
    AVLNode<T>* rightRotate(AVLNode<T>* y)
    {
        AVLNode<T>* x = y->left;
        AVLNode<T>* temp = x->right;

        x->right = y;
        y->left = temp;
        y->height = bigger(nodeHeight(y->left), nodeHeight(y->right)) + 1;
        x->height = bigger(nodeHeight(x->left), nodeHeight(x->right)) + 1;
        return x;
    }
    AVLNode<T>* leftRotate(AVLNode<T>* x)
    {
        AVLNode<T>* y = x->right;
        AVLNode<T>* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = bigger(nodeHeight(x->left), nodeHeight(x->right)) + 1;
        y->height = bigger(nodeHeight(y->left), nodeHeight(y->right)) + 1;
        return y;
    }
    AVLNode<T>* insertNode(AVLNode<T>* node, T value)
    {
        if (node == NULL)
        {
            return new AVLNode<T>(value);
        }

        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
        {
            return node;
        }

        node->height = bigger(nodeHeight(node->left), nodeHeight(node->right)) + 1;
        int b = balance(node);
        if (b > 1 && value < node->left->data)
        {
            return rightRotate(node);
        }
        if (b < -1 && value > node->right->data)
        {
            return leftRotate(node);
        }
        if (b > 1 && value > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }if (b < -1 && value < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    bool searchNode(AVLNode<T>* node, T value) const
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->data == value)
        {
            return true;
        }
        if (value < node->data)
        {
            return searchNode(node->left, value);
        }
        return searchNode(node->right, value);
    }
    void inorderNode(AVLNode<T>* node) const
    {
        if (node != NULL)
        {
            inorderNode(node->left);
            cout << node->data << " ";
            inorderNode(node->right);
        }
    }

    void clearNode(AVLNode<T>* node)
    {
        if (node != NULL)
        {
            clearNode(node->left);
            clearNode(node->right);
            delete node;
        }
    }
public:
    AVL()
    {
        root = NULL;
    }
    ~AVL()
    {
        clear();
    }
    void insert(T value)
    {
        root = insertNode(root, value);
    }
    bool search(T value) const
    {
        return searchNode(root, value);
    }



    void inorder() const
    {
        if (root == NULL)
        {
            cout << "Empty" << endl;
        }
        else
        {
            inorderNode(root);
        }

        cout << endl;
    }

    void clear()
    {
        clearNode(root);
        root = NULL;
    }
};

