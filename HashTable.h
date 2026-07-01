#pragma once
#include <iostream>
#include <string>
using namespace std;
template <class T>
class HashNode
{
public:
    string key;
    T value;
    HashNode<T>* next;

    HashNode(string k, T v)
    {
        key = k;
        value = v;
        next = NULL;
    }
};
template <class T>
class HashTable
{
private:
    static const int TABLE_SIZE = 101;
    HashNode<T>* table[TABLE_SIZE];

    int hashFunction(string key) const
    {
        int value = 0;
        for (int i = 0; i < (int)key.length(); i++)
        {
            value = (value * 31 + key[i]) % TABLE_SIZE;
        }

        if (value < 0)
        {
            value = value * -1;
        }
        return value;
    }

public:
    HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            table[i] = NULL;
        }
    }

    ~HashTable()
    {
        clear();
    }

    void insert(string key, T value)
    {
        int index = hashFunction(key);
        HashNode<T>* current = table[index];

        while (current != NULL)
        {
            if (current->key == key)
            {
                current->value = value;
                return;
            }

            current = current->next;
        }

        HashNode<T>* newNode = new HashNode<T>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }
    bool search(string key, T& value) const
    {
        int index = hashFunction(key);
        HashNode<T>* current = table[index];

        while (current != NULL)
        {
            if (current->key == key)
            {
                value = current->value;
                return true;
            }
            current = current->next;
        }

        return false;
    }
    bool remove(string key)
    {
        int index = hashFunction(key);
        HashNode<T>* current = table[index];
        HashNode<T>* previous = NULL;
        while (current != NULL)
        {
            if (current->key == key)
            {
                if (previous == NULL)
                {
                    table[index] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    void clear()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode<T>* current = table[i];

            while (current != NULL)
            {
                HashNode<T>* deleteNode = current;
                current = current->next;
                delete deleteNode;
            }
            table[i] = NULL;
        }
    }
    void showKeys() const
    {
        bool found = false;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode<T>* current = table[i];

            while (current != NULL)
            {
                cout << current->key << " ";
                found = true;
                current = current->next;
            }
        }
        if (found == false)
        {
            cout << "Empty";
        }
        cout << endl;
    }
};


