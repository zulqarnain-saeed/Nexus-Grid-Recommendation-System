#pragma once 
#include <iostream>
using namespace std;
template <class T>
class Queue
{
private:
    T* data;
    int frontIndex;
    int rearIndex;
    int used;
    int totalSize;
    void makeBigger()
    {
        int newSize = totalSize * 2;
        T* newData = new T[newSize];
        for (int i = 0; i < used; i++)
        {
            newData[i] = data[(frontIndex + i) % totalSize];
        }
        delete[] data;
        data = newData;
        totalSize = newSize;
        frontIndex = 0;
        rearIndex = used - 1;
    }
public:
    Queue(int size = 10)
    {
        if (size <= 0)
        {
            size = 10;
        }
        totalSize = size;
        data = new T[totalSize];
        frontIndex = 0;
        rearIndex = -1;
        used = 0;
    }
    Queue(const Queue<T>& other)
    {
        totalSize = other.totalSize;
        used = other.used;
        data = new T[totalSize];
        frontIndex = 0;
        rearIndex = used - 1;

        for (int i = 0; i < used; i++)
        {
            data[i] = other.data[(other.frontIndex + i) % other.totalSize];
        }
    }

    Queue<T>& operator=(const Queue<T>& other)
    {
        if (this != &other)
        {
            delete[] data;
            totalSize = other.totalSize;
            used = other.used;
            data = new T[totalSize];
            frontIndex = 0;
            rearIndex = used - 1;

            for (int i = 0; i < used; i++)
            {
                data[i] = other.data[(other.frontIndex + i) % other.totalSize];
            }
        }
        return *this;
    }

    ~Queue()
    {
        delete[] data;
    }

    bool enqueue(T value)
    {
        if (used == totalSize)
        {
            makeBigger();
        }
        rearIndex = (rearIndex + 1) % totalSize;
        data[rearIndex] = value;
        used++;
        return true;
    }

    bool dequeue(T& value)
    {
        if (isEmpty())
        {
            return false;
        }

        value = data[frontIndex];
        frontIndex = (frontIndex + 1) % totalSize;
        used--;

        if (used == 0)
        {
            frontIndex = 0;
            rearIndex = -1;
        }

        return true;
    }

    bool getFront(T& value) const
    {
        if (isEmpty())
        {
            return false;
        }

        value = data[frontIndex];
        return true;
    }

    bool isEmpty() const
    {
        return used == 0;
    }
    int size() const
    {
        return used;
    }

    void clear()
    {
        frontIndex = 0;
        rearIndex = -1;
        used = 0;
    }
};

