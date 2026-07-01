#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;
template <class T>
class BSTNode
{
public:
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(T value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};
template <class T>
class BST
{
private:
    BSTNode<T>* root;

    BSTNode<T>* insertNode(BSTNode<T>* node, T value)
    {
        if (node == NULL)
        {
            return new BSTNode<T>(value);
        }

        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }

        return node;
    }


    bool searchNode(BSTNode<T>* node, T value)
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

    BSTNode<T>* getMin(BSTNode<T>* node)
    {
        while (node != NULL && node->left != NULL)
        {
            node = node->left;
        }

        return node;
    }
    BSTNode<T>* deleteNode(BSTNode<T>* node, T value)
    {
        if (node == NULL)
        {
            return NULL;
        }
        if (value < node->data)
        {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteNode(node->right, value);
        }
        else
        {
            if (node->left == NULL)
            {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == NULL)
            {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode<T>* temp = getMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }
    void inorderNode(BSTNode<T>* node) const
    {
        if (node != NULL)
        {
            inorderNode(node->left);
            cout << node->data << " ";
            inorderNode(node->right);
        }
    }
    void preorderNode(BSTNode<T>* node) const
    {
        if (node != NULL)
        {
            cout << node->data << " ";
            preorderNode(node->left);
            preorderNode(node->right);
        }
    }
    void postorderNode(BSTNode<T>* node) const
    {
        if (node != NULL)
        {
            postorderNode(node->left);
            postorderNode(node->right);
            cout << node->data << " ";
        }
    }
    void clearNode(BSTNode<T>* node)
    {
        if (node != NULL)
        {
            clearNode(node->left);
            clearNode(node->right);
            delete node;
        }
    }

public:
    BST()
    {
        root = NULL;
    }


    void insert(T value)
    {
        root = insertNode(root, value);
    }

    bool search(T value) const
    {
        return searchNode(root, value);
    }

    void remove(T value)
    {
        root = deleteNode(root, value);
    }

    void inorder() const
    {
        if (root == NULL)
        {
            cout << "Empty";
        }
        else
        {
            inorderNode(root);
        }

        cout << endl;
    }

    void preorder()
    {
        if (root == NULL)
        {
            cout << "Empty";
        }
        else
        {
            preorderNode(root);
        }

        cout << endl;
    }

    void postorder()
    {
        if (root == NULL)
        {
            cout << "Empty";
        }
        else
        {
            postorderNode(root);
        }

        cout << endl;
    }

    void clear()
    {
        clearNode(root);
        root = NULL;
    }
};

#endif
