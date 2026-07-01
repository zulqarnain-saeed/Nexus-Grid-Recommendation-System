#ifndef EMERGENCY_DISPATCHER_H
#define EMERGENCY_DISPATCHER_H
#include <iostream>
#include <fstream>
#include <string>
#include "MaxHeap.h"
#include "CircularQueue.h"
using namespace std;
class EmergencyDispatcher
{
private:
    MaxHeap emergencyHeap;
    CircularQueue<string> waitingAreas;
    int nextId;
public:
    EmergencyDispatcher() : emergencyHeap(20), waitingAreas(20)
    {
        nextId = 1;
    }
    bool addEmergency(string location, int severity, int waitingTime)
    {
        if (location == "")
        {
            return false;
        }
        if (severity < 1 || severity > 10)
        {
            return false;
        }
        if (waitingTime < 0)
        {
            return false;
        }
        Emergency emergency(nextId, location, severity, waitingTime);
        emergencyHeap.insert(emergency);
        waitingAreas.enqueue(location);
        nextId++;
        cout << "Emergency added successfully." << endl;
        emergency.show();
        return true;
    }
    bool processEmergency(string logFileName)
    {
        Emergency emergency;
        if (emergencyHeap.extractMax(emergency) == false)
        {
            cout << "No emergency is waiting." << endl;
            return false;
        }
        cout << "Processing highest priority emergency:" << endl;
        emergency.show();
        ofstream outFile(logFileName.c_str(), ios::app);
        if (outFile)
        {
            outFile << "Processed emergency ID " << emergency.getId() << " at " << emergency.getLocation() << " with priority " << emergency.getPriorityScore() << endl;
            outFile.close();
        }
        else
        {
            cout << "Warning: log file could not be updated!" << endl;
        }
        return true;
    }
    void showNextEmergency() const
    {
        Emergency emergency;
        if (emergencyHeap.peek(emergency) == false)
        {
            cout << "No emergency is waiting" << endl;
            return;
        }
        cout << "Next emergency in heap:" << endl;
        emergency.show();
    }
    void rotateWaitingArea()
    {
        string area;
        if (waitingAreas.rotate(area) == false)
        {
            cout << "No waiting area in circular queue." << endl;
            return;
        }
        cout << "Circular queue moved to area: " << area << endl;
    }
    int waitingCount()
    {
        return emergencyHeap.size();
    }
};
#endif
