#pragma once
#include <iostream>
#include <string>
using namespace std;
class Vehicle
{
protected:
    string vehicleId;
    string location;
    int speed;
public:
    Vehicle(string id, string place, int spd)
    {
        vehicleId = id;
        location = place;
        speed = spd;
    }

    virtual ~Vehicle()
    {
    }

    string getId() const
    {
        return vehicleId;
    }

    string getLocation() const
    {
        return location;
    }

    int getSpeed() const
    {
        return speed;
    }

    void setLocation(string place)
    {
        location = place;
    }

    virtual void move() = 0;
    virtual void showInfo() = 0;
};

class Ambulance : public Vehicle
{
private:
    int bedCount;

public:
    Ambulance(string id, string place, int spd, int beds) : Vehicle(id, place, spd)
    {
        bedCount = beds;
    }

    void move() override
    {
        cout << "Ambulance " << vehicleId << " is moving from " << location << " for emergency help." << endl;
    }

    void showInfo() override
    {
        cout << "Vehicle Type: Ambulance" << endl;
        cout << "ID: " << vehicleId << endl;
        cout << "Location: " << location << endl;
        cout << "Speed: " << speed << " km/h" << endl;
        cout << "Bed Capacity: " << bedCount << endl;
    }
};

class Truck : public Vehicle
{
private:
    int loadLimit;

public:
    Truck(string id, string place, int spd, int load) : Vehicle(id, place, spd)
    {
        loadLimit = load;
    }

    void move() override
    {
        cout << "Truck " << vehicleId << " is moving from " << location << " with relief supplies." << endl;
    }

    void showInfo() override
    {
        cout << "Vehicle Type: Truck" << endl;
        cout << "ID: " << vehicleId << endl;
        cout << "Location: " << location << endl;
        cout << "Speed: " << speed << " km/h" << endl;
        cout << "Load Limit: " << loadLimit << " kg" << endl;
    }
};

class ElectricBike : public Vehicle
{
private:
    int batteryLevel;

public:
    ElectricBike(string id, string place, int spd, int battery) : Vehicle(id, place, spd)
    {
        batteryLevel = battery;
    }

    void move() override
    {
        cout << "Electric Bike " << vehicleId << " is moving from " << location << " for quick city support." << endl;
    }

    void showInfo() override
    {
        cout << "Vehicle Type: Electric Bike" << endl;
        cout << "ID: " << vehicleId << endl;
        cout << "Location: " << location << endl;
        cout << "Speed: " << speed << " km/h" << endl;
        cout << "Battery: " << batteryLevel << "%" << endl;
    }
};

