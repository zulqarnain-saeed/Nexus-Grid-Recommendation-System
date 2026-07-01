#pragma once
#include <iostream>
using namespace std;
template <class T>
class CircularQueue
{
private:
    T* data;
    int frontIndex;
    int rearIndex;
    int used;
    int totalSize;
public:
    CircularQueue(int size = 10)
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
    CircularQueue(const CircularQueue<T>& other)
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
    CircularQueue<T>& operator=(const CircularQueue<T>& other)
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
    ~CircularQueue()
    {
        delete[] data;
    }

    bool enqueue(T value)
    {
        if (isFull())
        {
            return false;
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

    bool rotate(T& value)
    {
        if (dequeue(value) == false)
        {
            return false;
        }

        enqueue(value);
        return true;
    }
    bool isFull()
    {
        return used == totalSize;
    }
    bool isEmpty() const
    {
        return used == 0;
    }
    int size() const
    {
        return used;
    }
    int capacity()
    {
        return totalSize;
    }
};


