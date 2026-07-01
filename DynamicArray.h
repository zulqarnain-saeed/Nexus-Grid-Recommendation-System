#pragma once 
#include <iostream>
using namespace std;
template <class T>
class DynamicArray
{
private:
    T* data;
    int used;
    int totalSize;
    void makeBigger()
    {
        int newSize = totalSize * 2;
        T* newData = new T[newSize];
        for (int i = 0; i < used; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        totalSize = newSize;
    }
public:
    DynamicArray(int size = 10)
    {
        if (size <= 0)
        {
            size = 10;
        }
        used = 0;
        totalSize = size;
        data = new T[totalSize];
    }
    DynamicArray(const DynamicArray<T>& other)
    {
        used = other.used;
        totalSize = other.totalSize;
        data = new T[totalSize];
        for (int i = 0; i < used; i++)
        {
            data[i] = other.data[i];
        }
    }
    DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        if (this != &other)
        {
            delete[] data;
            used = other.used;
            totalSize = other.totalSize;
            data = new T[totalSize];

            for (int i = 0; i < used; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~DynamicArray()
    {
        delete[] data;
    }
    bool add(T value)
    {
        if (used == totalSize)
        {
            makeBigger();
        }

        data[used] = value;
        used++;
        return true;
    }
    bool removeAt(int index)
    {
        if (index < 0 || index >= used)
        {
            return false;
        }

        for (int i = index; i < used - 1; i++)
        {
            data[i] = data[i + 1];
        }
        used--;
        return true;
    }

    bool getAt(int index, T& value) const
    {
        if (index < 0 || index >= used)
        {
            return false;
        }

        value = data[index];
        return true;
    }
    bool setAt(int index, T value)
    {
        if (index < 0 || index >= used)
        {
            return false;
        }
        data[index] = value;
        return true;
    }
    T& operator[](int index)
    {
        return data[index];
    }
    const T& operator[](int index) const
    {
        return data[index];
    }
    int size()
    {
        return used;
    }
    int capacity()
    {
        return totalSize;
    }

    bool isEmpty() const
    {
        return used == 0;
    }
    void clear()
    {
        used = 0;
    }
    void display() const
    {
        if (used == 0)
        {
            cout << "Empty" << endl;
            return;
        }
        for (int i = 0; i < used; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};


