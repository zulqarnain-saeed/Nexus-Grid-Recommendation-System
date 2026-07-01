#pragma once 
#include <iostream>
#include <string>
#include "Queue.h"
#include "Stack.h"
#include "MinHeap.h"
using namespace std;
class Graph
{
private:
    static const int MAX_VERTICES = 30;
    static const int INF = 1000000000;
    string names[MAX_VERTICES];
    int edges[MAX_VERTICES][MAX_VERTICES];
    int vertexCount;
    int findIndex(string name) const
    {
        for (int i = 0; i < vertexCount; i++)
        {
            if (names[i] == name)
            {
                return i;
            }
        }
        return -1;
    }
public:
    Graph()
    {
        vertexCount = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            for (int j = 0; j < MAX_VERTICES; j++)
            {
                if (i == j)
                {
                    edges[i][j] = 0;
                }
                else
                {
                    edges[i][j] = INF;
                }
            }
        }
    }
    void clear()
    {
        vertexCount = 0;

        for (int i = 0; i < MAX_VERTICES; i++)
        {
            for (int j = 0; j < MAX_VERTICES; j++)
            {
                if (i == j)
                {
                    edges[i][j] = 0;
                }
                else
                {
                    edges[i][j] = INF;
                }
            }
        }
    }

    bool addVertex(string name)
    {
        if (name == "")
        {
            return false;
        }

        if (findIndex(name) != -1)
        {
            return true;
        }

        if (vertexCount == MAX_VERTICES)
        {
            return false;
        }

        names[vertexCount] = name;
        vertexCount++;
        return true;
    }

    bool addEdge(string first, string second, int distance)
    {
        if (distance <= 0)
        {
            return false;
        }

        if (addVertex(first) == false)
        {
            return false;
        }

        if (addVertex(second) == false)
        {
            return false;
        }

        int firstIndex = findIndex(first);
        int secondIndex = findIndex(second);
        if (firstIndex == -1 || secondIndex == -1)
        {
            return false;
        }
        edges[firstIndex][secondIndex] = distance;
        edges[secondIndex][firstIndex] = distance;
        return true;
    }

    bool hasVertex(string name)
    {
        return findIndex(name) != -1;
    }

    int countVertices()
    {
        return vertexCount;
    }

    void showVertices() const
    {
        if (vertexCount == 0)
        {
            cout << "No locations loaded!" << endl;
            return;
        }

        cout << "Available locations: ";
        for (int i = 0; i < vertexCount; i++)
        {
            cout << names[i];
            if (i != vertexCount - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
    void displayMap()const
    {
        if (vertexCount == 0)
        {
            cout << "Map is empty. Load map first" << endl;
            return;
        }

        cout << "Road connections:" << endl;
        for (int i = 0; i < vertexCount; i++)
        {
            cout << names[i] << " -> ";
            bool found = false;
            for (int j = 0; j < vertexCount; j++)
            {
                if (i != j && edges[i][j] != INF)
                {
                    cout << names[j] << "(" << edges[i][j] << ") ";
                    found = true;
                }
            }
            if (found == false)
            {
                cout << "No road";
            }

            cout << endl;
        }
    }

    void bfs(string startName) const
    {
        int start = findIndex(startName);

        if (start == -1)
        {
            cout << "Start location not found" << endl;
            return;
        }

        bool visited[MAX_VERTICES];

        for (int i = 0; i < MAX_VERTICES; i++)
        {
            visited[i] = false;
        }
        Queue<int> q;
        visited[start] = true;
        q.enqueue(start);

        cout << "BFS: ";
        while (q.isEmpty() == false)
        {
            int current;
            q.dequeue(current);
            cout << names[current] << " ";

            for (int i = 0; i < vertexCount; i++)
            {
                if (edges[current][i] != INF && current != i && visited[i] == false)
                {
                    visited[i] = true;
                    q.enqueue(i);
                }
            }
        }
        cout << endl;
    }

    void dfs(string startName) const
    {
        int start = findIndex(startName);

        if (start == -1)
        {
            cout << "Start location not found" << endl;
            return;
        }

        bool visited[MAX_VERTICES];

        for (int i = 0; i < MAX_VERTICES; i++)
        {
            visited[i] = false;
        }

        Stack<int> st;
        st.push(start);

        cout << "DFS: ";
        while (st.isEmpty() == false)
        {
            int current;
            st.pop(current);
            if (visited[current] == true)
            {
                continue;
            }

            visited[current] = true;
            cout << names[current] << " ";

            for (int i = vertexCount - 1; i >= 0; i--)
            {
                if (edges[current][i] != INF && current != i && visited[i] == false)
                {
                    st.push(i);
                }
            }
        }
        cout << endl;
    }

    bool shortestRoute(string sourceName, string destinationName) const
    {
        int source = findIndex(sourceName);
        int destination = findIndex(destinationName);

        if (vertexCount == 0)
        {
            cout << "Map is empty. Load map first." << endl;
            return false;
        }
        if (source == -1)
        {
            cout << "Source location not found." << endl;
            return false;
        }

        if (destination == -1)
        {
            cout << "Destination location not found." << endl;
            return false;
        }

        int dist[MAX_VERTICES];
        int parent[MAX_VERTICES];
        bool visited[MAX_VERTICES];
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            dist[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }
        MinHeap heap;
        dist[source] = 0;
        heap.insert(source, 0);
        while (heap.isEmpty() == false)
        {
            RouteHeapNode currentNode;
            heap.extractMin(currentNode);
            int current = currentNode.vertex;
            if (current < 0 || current >= vertexCount)
            {
                continue;
            }

            if (visited[current] == true)
            {
                continue;
            }

            visited[current] = true;

            for (int i = 0; i < vertexCount; i++)
            {
                if (edges[current][i] != INF && current != i)
                {
                    if (dist[current] + edges[current][i] < dist[i])
                    {
                        dist[i] = dist[current] + edges[current][i];
                        parent[i] = current;
                        heap.insert(i, dist[i]);
                    }
                }
            }
        }

        if (dist[destination] == INF)
        {
            cout << "No route found between these locations." << endl;
            return false;
        }
        Stack<int> path;
        int crawl = destination;
        while (crawl != -1)
        {
            path.push(crawl);
            crawl = parent[crawl];
        }
        cout << "Fastest route: ";
        bool firstPrint = true;

        while (path.isEmpty() == false)
        {
            int locationIndex;
            path.pop(locationIndex);

            if (firstPrint == false)
            {
                cout << " -> ";
            }

            cout << names[locationIndex];
            firstPrint = false;
        }
        cout << endl;
        cout << "Total distance: " << dist[destination] << endl;
        return true;
    }
};


