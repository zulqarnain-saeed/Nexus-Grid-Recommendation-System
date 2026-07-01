#pragma once 

#include <iostream>
#include <string>
#include "RegressionModel.h"
using namespace std;

class Emergency
{
private:
    int emergencyId;
    string location;
    int severity;
    int waitingTime;
    double criticalProbability;
    double criticalOdds;
    double criticalLogit;
    double criticalRiskScore;
    double priorityScore;

    void calculateScores()
    {
        double severityFeature = (double)severity / 10.0;
        double waitingFeature = (double)waitingTime / 60.0;
        double busyAreaFeature = 1.0;
        double delayFeature = 0.0;
        double mixedFeature = ((double)severity * (double)waitingTime) / 100.0;

        if (waitingTime >= 20)
        {
            delayFeature = 1.0;
        }

        LogisticRegressionModel model(-2.20, 2.80, 1.60, 0.50, 1.00, 0.80);
        criticalProbability = model.predictProbability(severityFeature, waitingFeature, busyAreaFeature, delayFeature, mixedFeature);
        criticalOdds = model.calculateOdds(criticalProbability);
        criticalLogit = model.calculateLogit(criticalProbability);
        criticalRiskScore = model.calculateRiskScore(criticalProbability);
        priorityScore = (severity * 0.45) + (waitingTime * 0.07) + (criticalRiskScore * 0.10);
    }

public:
    Emergency()
    {
        emergencyId = 0;
        location = "";
        severity = 0;
        waitingTime = 0;
        criticalProbability = 0.0;
        criticalOdds = 0.0;
        criticalLogit = 0.0;
        criticalRiskScore = 0.0;
        priorityScore = 0.0;
    }

    Emergency(int id, string place, int sev, int wait)
    {
        emergencyId = id;
        location = place;
        severity = sev;
        waitingTime = wait;
        criticalProbability = 0.0;
        criticalOdds = 0.0;
        criticalLogit = 0.0;
        criticalRiskScore = 0.0;
        priorityScore = 0.0;
        calculateScores();
    }

    int getId() const
    {
        return emergencyId;
    }

    string getLocation() const
    {
        return location;
    }

    int getSeverity() const
    {
        return severity;
    }

    int getWaitingTime() const
    {
        return waitingTime;
    }

    double getCriticalProbability() const
    {
        return criticalProbability;
    }

    double getCriticalOdds() const
    {
        return criticalOdds;
    }

    double getCriticalLogit() const
    {
        return criticalLogit;
    }

    double getCriticalRiskScore() const
    {
        return criticalRiskScore;
    }

    double getPriorityScore() const
    {
        return priorityScore;
    }

    string getDispatchRecommendation() const
    {
        LogisticRegressionModel model(-2.20, 2.80, 1.60, 0.50, 1.00, 0.80);
        int decisionClass = model.calculateDecision(criticalProbability);

        if (decisionClass == 1 && (criticalProbability >= 0.80 || severity >= 8))
        {
            return "Send ambulance immediately";
        }
        else if (criticalProbability >= 0.50 || waitingTime >= 20)
        {
            return "Keep high priority and dispatch soon";
        }
        else
        {
            return "Keep in normal emergency queue";
        }
    }

    void show() const
    {
        cout << "Emergency ID: " << emergencyId << endl;
        cout << "Location: " << location << endl;
        cout << "Severity: " << severity << endl;
        cout << "Waiting Time: " << waitingTime << " minutes" << endl;
        LogisticRegressionModel model(-2.20, 2.80, 1.60, 0.50, 1.00, 0.80);
        cout << "Logistic Critical Probability: " << criticalProbability * 100.0 << "%" << endl;
        cout << "Logistic Odds: " << criticalOdds << endl;
        cout << "Logistic Logit: " << criticalLogit << endl;
        cout << "Risk Score: " << criticalRiskScore << endl;
        cout << "Decision Class: " << model.calculateDecision(criticalProbability) << endl;
        cout << "Risk Level: " << model.getRiskLevel(criticalProbability) << endl;
        cout << "Priority Score: " << priorityScore << endl;
        cout << "Dispatch Recommendation: " << getDispatchRecommendation() << endl;
    }
};

class MaxHeap
{
private:
    Emergency* data;
    int used;
    int totalSize;

    void swapItems(int first, int second)
    {
        Emergency temp = data[first];
        data[first] = data[second];
        data[second] = temp;
    }

    void makeBigger()
    {
        int newSize = totalSize * 2;
        Emergency* newData = new Emergency[newSize];

        for (int i = 0; i < used; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        totalSize = newSize;
    }

    void moveUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (data[parent].getPriorityScore() >= data[index].getPriorityScore())
            {
                break;
            }

            swapItems(parent, index);
            index = parent;
        }
    }

    void moveDown(int index)
    {
        while (true)
        {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int largest = index;

            if (left < used && data[left].getPriorityScore() > data[largest].getPriorityScore())
            {
                largest = left;
            }

            if (right < used && data[right].getPriorityScore() > data[largest].getPriorityScore())
            {
                largest = right;
            }

            if (largest == index)
            {
                break;
            }

            swapItems(index, largest);
            index = largest;
        }
    }

public:
    MaxHeap(int size = 20)
    {
        if (size <= 0)
        {
            size = 20;
        }

        totalSize = size;
        used = 0;
        data = new Emergency[totalSize];
    }

    MaxHeap(const MaxHeap& other)
    {
        totalSize = other.totalSize;
        used = other.used;
        data = new Emergency[totalSize];

        for (int i = 0; i < used; i++)
        {
            data[i] = other.data[i];
        }
    }

    MaxHeap& operator=(const MaxHeap& other)
    {
        if (this != &other)
        {
            delete[] data;
            totalSize = other.totalSize;
            used = other.used;
            data = new Emergency[totalSize];

            for (int i = 0; i < used; i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    ~MaxHeap()
    {
        delete[] data;
    }

    void insert(Emergency value)
    {
        if (used == totalSize)
        {
            makeBigger();
        }

        data[used] = value;
        moveUp(used);
        used++;
    }

    bool extractMax(Emergency& value)
    {
        if (used == 0)
        {
            return false;
        }

        value = data[0];
        data[0] = data[used - 1];
        used--;
        moveDown(0);
        return true;
    }

    bool peek(Emergency& value) const
    {
        if (used == 0)
        {
            return false;
        }

        value = data[0];
        return true;
    }

    int size() const
    {
        return used;
    }

    bool isEmpty() const
    {
        return used == 0;
    }
};

