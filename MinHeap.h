#pragma once 
#include <iostream>
using namespace std;
class RouteHeapNode
{
public:
    int vertex;
    int distance;
    RouteHeapNode()
    {
        vertex = -1;
        distance = 0;
    }
    RouteHeapNode(int v, int d)
    {
        vertex = v;
        distance = d;
    }
};
class MinHeap
{
private:
    RouteHeapNode* data;
    int used;
    int totalSize;
    void swapNodes(int first, int second)
    {
        RouteHeapNode temp = data[first];
        data[first] = data[second];
        data[second] = temp;
    }



    void moveUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (data[parent].distance <= data[index].distance)
            {
                break;
            }
            swapNodes(parent, index);
            index = parent;
        }
    }

    void moveDown(int index)
    {
        while (true)
        {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int smallest = index;
            if (left < used && data[left].distance < data[smallest].distance)
            {
                smallest = left;
            }

            if (right < used && data[right].distance < data[smallest].distance)
            {
                smallest = right;
            }
            if (smallest == index)
            {
                break;
            }

            swapNodes(index, smallest);
            index = smallest;
        }
    }
    void makeBigger()
    {
        int newSize = totalSize * 2;
        RouteHeapNode* newData = new RouteHeapNode[newSize];

        for (int i = 0; i < used; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        totalSize = newSize;
    }
public:
    MinHeap(int size = 50)
    {
        if (size <= 0)
        {
            size = 50;
        }
        totalSize = size;
        used = 0;
        data = new RouteHeapNode[totalSize];
    }

    ~MinHeap()
    {
        delete[] data;
    }
    void insert(int vertex, int distance)
    {
        if (used == totalSize)
        {
            makeBigger();
        }
        data[used] = RouteHeapNode(vertex, distance);
        moveUp(used);
        used++;
    }
    bool extractMin(RouteHeapNode& node)
    {
        if (used == 0)
        {
            return false;
        }
        node = data[0];
        data[0] = data[used - 1];
        used--;
        moveDown(0);
        return true;
    }


    bool isEmpty() const
    {
        return used == 0;
    }
};

