#pragma once 
#include <iostream>
using namespace std;
template <class T>
class CNode
{
public:
    T data;
    CNode<T>* next;
    CNode(T value)
    {
        data = value;
        next = NULL;
    }
};
template <class T>
class CircularLinkedList
{
private:
    CNode<T>* tail;
    CNode<T>* current;
public:
    CircularLinkedList()
    {
        tail = NULL;
        current = NULL;
    }
    void insert(T value)
    {
        CNode<T>* newNode = new CNode<T>(value);

        if (tail == NULL)
        {
            tail = newNode;
            tail->next = tail;
            current = tail;
            return;
        }
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    bool remove(T value)
    {
        if (tail == NULL)
        {
            return false;
        }

        CNode<T>* previous = tail;
        CNode<T>* node = tail->next;
        do
        {
            if (node->data == value)
            {
                if (node == tail && node == tail->next)
                {
                    delete node;
                    tail = NULL;
                    current = NULL;
                    return true;
                }
                previous->next = node->next;

                if (node == tail)
                {
                    tail = previous;
                }

                if (node == current)
                {
                    current = node->next;
                }

                delete node;
                return true;
            }

            previous = node;
            node = node->next;
        } while (previous != tail);

        return false;
    }

    bool search(T value) const
    {
        if (tail == NULL)
        {
            return false;
        }

        CNode<T>* start = tail->next;
        CNode<T>* node = start;
        do
        {
            if (node->data == value)
            {
                return true;
            }

            node = node->next;
        } while (node != start);

        return false;
    }

    bool moveNext(T& value)
    {
        if (current == NULL)
        {
            return false;
        }

        current = current->next;
        value = current->data;
        return true;
    }
    void display() const
    {
        if (tail == NULL)
        {
            cout << "Empty" << endl;
            return;
        }

        CNode<T>* start = tail->next;
        CNode<T>* node = start;
        do
        {
            cout << node->data << " ";
            node = node->next;
        } while (node != start);

        cout << endl;
    }
    void clear()
    {
        if (tail == NULL)
        {
            return;
        }

        CNode<T>* start = tail->next;
        CNode<T>* node = start;

        do
        {
            CNode<T>* deleteNode = node;
            node = node->next;
            delete deleteNode;
        } while (node != start);

        tail = NULL;
        current = NULL;
    }
};
