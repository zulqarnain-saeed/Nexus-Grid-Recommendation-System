#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "HashTable.h"
#include "Citizen.h"
using namespace std;
class FileHandler
{
public:
    bool loadMap(string fileName, Graph& graph)
    {
        ifstream inFile(fileName.c_str());
        if (!inFile)
        {
            cout << "Map file not found: " << fileName << endl;
            return false;
        }
        graph.clear();
        string first;
        string second;
        int distance;
        int loaded = 0;
        while (inFile >> first >> second >> distance)
        {
            if (graph.addEdge(first, second, distance))
            {
                loaded++;
            }
        }
        inFile.close();
        cout << loaded << " roads loaded." << endl;
        return loaded > 0;
    }
    bool loadCitizens(string fileName, HashTable<Citizen>& citizens)
    {
        ifstream inFile(fileName.c_str());
        if (!inFile)
        {
            cout << "Citizens file not found: " << fileName << endl;
            return false;
        }
        citizens.clear();
        string id;
        string name;
        string area;
        int loaded = 0;
        while (inFile >> id >> name >> area)
        {
            Citizen citizen(id, name, area);
            citizens.insert(id, citizen);
            loaded++;
        }
        inFile.close();
        cout << loaded << " citizens loaded." << endl;
        return loaded > 0;
    }
    bool appendLog(string fileName, string message)
    {
        ofstream outFile(fileName.c_str(), ios::app);

        if (!outFile)
        {
            cout << "Unable to open log file: " << fileName << endl;
            return false;
        }
        outFile << message << endl;
        outFile.close();
        return true;
    }
    bool readWholeFile(string fileName, string& text)
    {
        ifstream inFile(fileName.c_str());
        if (!inFile)
        {
            return false;
        }

        text = "";
        string line;
        while (getline(inFile, line))
        {
            text += line;
            text += '\n';
        }
        inFile.close();
        return true;
    }
};
#endif
