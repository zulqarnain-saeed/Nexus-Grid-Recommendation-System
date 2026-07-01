#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;
class NavigationSystem
{
private:
    Graph cityGraph;
public:
    Graph& getGraph()
    {
        return cityGraph;
    }
    void clear()
    {
        cityGraph.clear();
    }
    void showMap() const
    {
        cityGraph.displayMap();
    }

    void showLocations() const
    {
        cityGraph.showVertices();
    }

    void findFastestRoute(string source, string destination) const
    {
        cityGraph.shortestRoute(source, destination);
    }

    void showBfs(string source) const
    {
        cityGraph.bfs(source);
    }
    void showDfs(string source) const
    {
        cityGraph.dfs(source);
    }
};

