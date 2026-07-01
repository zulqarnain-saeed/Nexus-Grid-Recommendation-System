#pragma once 
#include <iostream>
using namespace std;
template <class T>
class DNode
{
public:
    T data;
    DNode<T>* next;
    DNode<T>* previous;
    DNode(T value)
    {
        data = value;
        next = NULL;
        previous = NULL;
    }
};
template <class T>
class DoublyLinkedList
{
private:
    DNode<T>* head;
    DNode<T>* tail;
public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    ~DoublyLinkedList()
    {
        clear();
    }
    void insertAtStart(T value)
    {
        DNode<T>* newNode = new DNode<T>(value);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            return;
        }
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    void insertAtEnd(T value)
    {
        DNode<T>* newNode = new DNode<T>(value);

        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    bool deleteValue(T value)
    {
        if (head == NULL)
        {
            return false;
        }

        DNode<T>* current = head;
        while (current != NULL)
        {
            if (current->data == value)
            {
                if (current == head)
                {
                    head = current->next;
                }
                else
                {
                    current->previous->next = current->next;
                }
                if (current == tail)
                {
                    tail = current->previous;
                }
                else
                {
                    current->next->previous = current->previous;
                }

                delete current;
                return true;
            }

            current = current->next;
        }
        return false;
    }

    bool search(T value) const
    {
        DNode<T>* current = head;
        while (current != NULL)
        {
            if (current->data == value)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void displayForward() const
    {
        if (head == NULL)
        {
            cout << "Empty" << endl;
            return;
        }
        DNode<T>* current = head;
        while (current != NULL)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    void displayBackward() const
    {
        if (tail == NULL)
        {
            cout << "Empty" << endl;
            return;
        }
        DNode<T>* current = tail;
        while (current != NULL)
        {
            cout << current->data << " ";
            current = current->previous;
        }
        cout << endl;
    }
    void clear()
    {
        while (head != NULL)
        {
            DNode<T>* deleteNode = head;
            head = head->next;
            delete deleteNode;
        }
        tail = NULL;
    }
};

