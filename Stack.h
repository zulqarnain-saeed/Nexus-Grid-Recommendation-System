#pragma once 
#include <iostream>
using namespace std;
template <class T>
class Stack
{
private:
    T* data;
    int topIndex;
    int totalSize;
    void makeBigger()
    {
        int newSize = totalSize * 2;
        T* newData = new T[newSize];
        for (int i = 0; i <= topIndex; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        totalSize = newSize;
    }
public:
    Stack(int size = 10)
    {
        if (size <= 0)
        {
            size = 10;
        }

        totalSize = size;
        topIndex = -1;
        data = new T[totalSize];
    }

    Stack(const Stack<T>& other)
    {
        totalSize = other.totalSize;
        topIndex = other.topIndex;
        data = new T[totalSize];

        for (int i = 0; i <= topIndex; i++)
        {
            data[i] = other.data[i];
        }
    }

    Stack<T>& operator=(const Stack<T>& other)
    {
        if (this != &other)
        {
            delete[] data;
            totalSize = other.totalSize;
            topIndex = other.topIndex;
            data = new T[totalSize];

            for (int i = 0; i <= topIndex; i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    ~Stack()
    {
        delete[] data;
    }

    bool push(T value)
    {
        if (topIndex == totalSize - 1)
        {
            makeBigger();
        }

        topIndex++;
        data[topIndex] = value;
        return true;
    }

    bool pop(T& value)
    {
        if (isEmpty())
        {
            return false;
        }

        value = data[topIndex];
        topIndex--;
        return true;
    }

    bool peek(T& value) const
    {
        if (isEmpty())
        {
            return false;
        }

        value = data[topIndex];
        return true;
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    int size() const
    {
        return topIndex + 1;
    }

    void clear()
    {
        topIndex = -1;
    }
};

