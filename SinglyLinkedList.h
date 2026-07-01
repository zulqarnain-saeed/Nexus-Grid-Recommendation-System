#pragma once 
#include <iostream>
using namespace std;

template <class T>
class SNode
{
public:
    T data;
    SNode<T>* next;

    SNode(T value)
    {
        data = value;
        next = NULL;
    }
};
template <class T>
class SinglyLinkedList
{
private:
    SNode<T>* head;

public:
    SinglyLinkedList()
    {
        head = NULL;
    }

    ~SinglyLinkedList()
    {
        clear();
    }

    void insertAtStart(T value)
    {
        SNode<T>* newNode = new SNode<T>(value);
        newNode->next = head;
        head = newNode;
    }
    void insertAtEnd(T value)
    {
        SNode<T>* newNode = new SNode<T>(value);

        if (head == NULL)
        {
            head = newNode;
            return;
        }
        SNode<T>* temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    bool deleteValue(T value)
    {
        if (head == NULL)
        {
            return false;
        }

        if (head->data == value)
        {
            SNode<T>* deleteNode = head;
            head = head->next;
            delete deleteNode;
            return true;
        }

        SNode<T>* previous = head;
        SNode<T>* current = head->next;

        while (current != NULL)
        {
            if (current->data == value)
            {
                previous->next = current->next;
                delete current;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    bool search(T value) const
    {
        SNode<T>* temp = head;

        while (temp != NULL)
        {
            if (temp->data == value)
            {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }
    bool isEmpty() const
    {
        return head == NULL;
    }void display() const
    {
        if (head == NULL)
        {
            cout << "Empty" << endl;
            return;
        }

        SNode<T>* temp = head;

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    void clear()
    {
        while (head != NULL)
        {
            SNode<T>* deleteNode = head;
            head = head->next;
            delete deleteNode;
        }
    }
};

