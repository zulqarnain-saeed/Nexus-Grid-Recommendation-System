#ifndef CITIZEN_H
#define CITIZEN_H
#include <iostream>
#include <string>
using namespace std;
class Citizen
{
private:
    string citizenId;
    string name;
    string area;
public:
    Citizen()
    {
        citizenId = "";
        name = "";
        area = "";
    }
    Citizen(string id, string citizenName, string citizenArea)
    {
        citizenId = id;
        name = citizenName;
        area = citizenArea;
    }
    string getId() const
    {
        return citizenId;
    }
    string getName() const
    {
        return name;
    }
    string getArea() const
    {
        return area;
    }
    void show() const
    {
        cout << "Citizen ID: " << citizenId << endl;
        cout << "Name: " << name << endl;
        cout << "Area: " << area << endl;
    }
};
#endif
