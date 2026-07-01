#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "HashTable.h"
#include "AVL.h"
#include "BST.h"
#include "RegressionModel.h"
using namespace std;

class InventoryItem
{
private:
    static const int MAX_HISTORY = 7;
    string name;
    int quantity;
    int dailyUse;
    int thresholdDays;
    int demandHistory[MAX_HISTORY];
    int demandCount;

public:
    InventoryItem()
    {
        name = "";
        quantity = 0;
        dailyUse = 1;
        thresholdDays = 3;
        demandCount = 0;

        for (int i = 0; i < MAX_HISTORY; i++)
        {
            demandHistory[i] = 0;
        }
    }

    InventoryItem(string itemName, int itemQuantity, int itemDailyUse, int itemThreshold)
    {
        name = itemName;
        quantity = itemQuantity;
        dailyUse = itemDailyUse;
        thresholdDays = itemThreshold;
        demandCount = 0;

        for (int i = 0; i < MAX_HISTORY; i++)
        {
            demandHistory[i] = 0;
        }

        if (dailyUse <= 0)
        {
            dailyUse = 1;
        }

        if (thresholdDays < 0)
        {
            thresholdDays = 0;
        }
    }

    string getName() const
    {
        return name;
    }

    int getQuantity() const
    {
        return quantity;
    }

    int getDailyUse() const
    {
        return dailyUse;
    }

    int getThresholdDays() const
    {
        return thresholdDays;
    }

    int getDemandCount() const
    {
        return demandCount;
    }

    void setDemandHistory(const int historyValues[], int count)
    {
        if (count > MAX_HISTORY)
        {
            count = MAX_HISTORY;
        }

        if (count < 0)
        {
            count = 0;
        }

        demandCount = count;

        for (int i = 0; i < MAX_HISTORY; i++)
        {
            if (i < demandCount)
            {
                if (historyValues[i] < 0)
                {
                    demandHistory[i] = 0;
                }
                else
                {
                    demandHistory[i] = historyValues[i];
                }
            }
            else
            {
                demandHistory[i] = 0;
            }
        }
    }

    int daysLeft() const
    {
        if (dailyUse <= 0)
        {
            return 0;
        }

        return quantity / dailyUse;
    }

    bool needsRestock() const
    {
        return daysLeft() <= thresholdDays;
    }

    double getDemandTrend() const
    {
        if (demandCount < 2)
        {
            return 0.0;
        }

        return (double)(demandHistory[demandCount - 1] - demandHistory[0]) / (double)(demandCount - 1);
    }

    double predictNextDailyUse() const
    {
        if (demandCount < 2)
        {
            return (double)dailyUse;
        }

        double xValues[MAX_HISTORY];
        double yValues[MAX_HISTORY];

        for (int i = 0; i < demandCount; i++)
        {
            xValues[i] = (double)(i + 1);
            yValues[i] = (double)demandHistory[i];
        }

        LinearRegressionModel model;

        if (model.train(xValues, yValues, demandCount) == false)
        {
            return (double)dailyUse;
        }

        double lastDemand = yValues[demandCount - 1];
        double prediction = model.predictFinal((double)demandCount + 1.0, lastDemand);

        if (prediction < 1.0)
        {
            prediction = 1.0;
        }

        return prediction;
    }

    double predictedDaysLeft() const
    {
        double predictedUse = predictNextDailyUse();

        if (predictedUse <= 0.0)
        {
            return 0.0;
        }

        return quantity / predictedUse;
    }

    double restockRiskProbability() const
    {
        double predictedUse = predictNextDailyUse();
        double predictedDays = predictedDaysLeft();
        double shortageGap = (double)thresholdDays - predictedDays;
        double demandPressure = predictedUse / (double)(dailyUse + 1);
        double fastUseScore = predictedUse / 20.0;
        double lowStockRatio = 1.0 / (predictedDays + 1.0);
        double trendFeature = getDemandTrend() / 10.0;

        LogisticRegressionModel model(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        return model.predictProbability(shortageGap, demandPressure, fastUseScore, lowStockRatio, trendFeature);
    }

    double restockOdds() const
    {
        LogisticRegressionModel model(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        return model.calculateOdds(restockRiskProbability());
    }

    double restockLogit() const
    {
        LogisticRegressionModel model(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        return model.calculateLogit(restockRiskProbability());
    }

    int restockDecisionClass() const
    {
        LogisticRegressionModel model(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        return model.calculateDecision(restockRiskProbability());
    }

    double restockRiskScore() const
    {
        LogisticRegressionModel model(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        return model.calculateRiskScore(restockRiskProbability());
    }

    string restockRiskLevel() const
    {
        LogisticRegressionModel model(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        return model.getRiskLevel(restockRiskProbability());
    }

    double suggestedOrderQuantity() const
    {
        double safeDays = (double)thresholdDays + 3.0;
        LinearRegressionModel model;
        return model.calculateRecommendedOrder(predictNextDailyUse(), safeDays, (double)quantity);
    }

    string getRecommendation() const
    {
        double probability = restockRiskProbability();
        double days = predictedDaysLeft();
        double orderQuantity = suggestedOrderQuantity();

        if (probability >= 0.75 || days <= (double)thresholdDays)
        {
            if (orderQuantity > 0.0)
            {
                return "RESTOCK IMMEDIATELY";
            }

            return "Monitor closely";
        }
        else if (probability >= 0.45)
        {
            return "RESTOCK SOON";
        }
        else
        {
            return "Stock is okay";
        }
    }

    void show() const
    {
        cout << "Item Name: " << name << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Daily Use: " << dailyUse << endl;
        cout << "Old Days Left Formula: quantity / dailyUse = " << daysLeft() << endl;
        cout << "Regression Predicted Tomorrow Use: " << predictNextDailyUse() << endl;
        cout << "Logistic Restock Risk: " << restockRiskScore() << "%" << endl;
        cout << "Suggested Order Quantity: " << suggestedOrderQuantity() << endl;
        cout << "Regression Recommendation: " << getRecommendation() << endl;
    }

    void showRegressionReport() const
    {
        cout << "Item Name: " << name << endl;
        cout << "Current Quantity: " << quantity << endl;
        cout << "Normal Daily Use: " << dailyUse << endl;
        cout << "Threshold Days: " << thresholdDays << endl;

        if (demandCount >= 2)
        {
            double xValues[MAX_HISTORY];
            double yValues[MAX_HISTORY];

            cout << "Demand History: ";
            for (int i = 0; i < demandCount; i++)
            {
                cout << demandHistory[i] << " ";
                xValues[i] = (double)(i + 1);
                yValues[i] = (double)demandHistory[i];
            }
            cout << endl;

            LinearRegressionModel linearModel;
            linearModel.train(xValues, yValues, demandCount);
            linearModel.showFormula();
            linearModel.showSixMathematicalFormulas();
            cout << "MSE Value: " << linearModel.getMeanSquaredError() << endl;
            cout << "Average Growth Value: " << linearModel.getAverageGrowth() << endl;
        }
        else
        {
            LinearRegressionModel linearModel;
            cout << "Demand History: not available, using normal daily use" << endl;
            cout << "Linear Regression Formula: y = a + bx, history needed for training" << endl;
            linearModel.showSixMathematicalFormulas();
        }

        LogisticRegressionModel logisticModel(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        logisticModel.showFormula();
        logisticModel.showSixLogisticFormulas();

        cout << "Predicted Tomorrow Use: " << predictNextDailyUse() << endl;
        cout << "Predicted Days Left: " << predictedDaysLeft() << endl;
        cout << "Restock Risk Probability: " << restockRiskProbability() * 100.0 << "%" << endl;
        cout << "Restock Odds: " << restockOdds() << endl;
        cout << "Restock Logit: " << restockLogit() << endl;
        cout << "Decision Class: " << restockDecisionClass() << endl;
        cout << "Risk Level: " << restockRiskLevel() << endl;
        cout << "Suggested Order Quantity: " << suggestedOrderQuantity() << endl;
        cout << "Final Recommendation: " << getRecommendation() << endl;
    }
};

class ResourceManager
{
private:
    static const int MAX_ITEMS = 100;
    InventoryItem items[MAX_ITEMS];
    int itemCount;
    HashTable<int> indexTable;
    AVL<string> itemNameTree;
    BST<int> quantityTree;

public:
    ResourceManager()
    {
        itemCount = 0;
    }

    void clear()
    {
        itemCount = 0;
        indexTable.clear();
        itemNameTree.clear();
        quantityTree.clear();
    }

    bool addItem(string name, int quantity, int dailyUse, int thresholdDays)
    {
        if (name == "")
        {
            return false;
        }

        if (quantity < 0 || dailyUse <= 0 || thresholdDays < 0)
        {
            return false;
        }

        int oldIndex;

        if (indexTable.search(name, oldIndex))
        {
            items[oldIndex] = InventoryItem(name, quantity, dailyUse, thresholdDays);
            return true;
        }

        if (itemCount == MAX_ITEMS)
        {
            return false;
        }

        items[itemCount] = InventoryItem(name, quantity, dailyUse, thresholdDays);
        indexTable.insert(name, itemCount);
        itemNameTree.insert(name);
        quantityTree.insert(quantity);
        itemCount++;
        return true;
    }

    bool loadFromFile(string fileName)
    {
        ifstream inFile(fileName.c_str());

        if (!inFile)
        {
            cout << "Inventory file not found: " << fileName << endl;
            return false;
        }

        clear();

        string name;
        int quantity;
        int dailyUse;
        int threshold;
        int loaded = 0;

        while (inFile >> name >> quantity >> dailyUse >> threshold)
        {
            if (addItem(name, quantity, dailyUse, threshold))
            {
                loaded++;
            }
        }

        inFile.close();
        cout << loaded << " inventory items loaded." << endl;
        return loaded > 0;
    }

    bool loadDemandHistoryFromFile(string fileName)
    {
        ifstream inFile(fileName.c_str());

        if (!inFile)
        {
            cout << "Demand history file not found: " << fileName << endl;
            return false;
        }

        string name;
        int history[7];
        int loaded = 0;

        while (inFile >> name >> history[0] >> history[1] >> history[2] >> history[3] >> history[4] >> history[5] >> history[6])
        {
            int index;

            if (indexTable.search(name, index) && index >= 0 && index < itemCount)
            {
                items[index].setDemandHistory(history, 7);
                loaded++;
            }
        }

        inFile.close();
        cout << loaded << " demand history records loaded for regression." << endl;
        return loaded > 0;
    }

    bool searchItem(string name, InventoryItem& item) const
    {
        int index;

        if (indexTable.search(name, index) == false)
        {
            return false;
        }

        if (index < 0 || index >= itemCount)
        {
            return false;
        }

        item = items[index];
        return true;
    }

    void showItem(string name) const
    {
        InventoryItem item;

        if (searchItem(name, item) == false)
        {
            cout << "Item not found." << endl;
            return;
        }

        item.show();
    }

    void showRegressionForItem(string name) const
    {
        InventoryItem item;

        if (searchItem(name, item) == false)
        {
            cout << "Item not found." << endl;
            return;
        }

        item.showRegressionReport();
    }

    void showAll() const
    {
        if (itemCount == 0)
        {
            cout << "Inventory is empty." << endl;
            return;
        }

        for (int i = 0; i < itemCount; i++)
        {
            cout << "--------------------" << endl;
            items[i].show();
        }
    }

    void showLowStock() const
    {
        if (itemCount == 0)
        {
            cout << "Inventory is empty." << endl;
            return;
        }

        bool found = false;

        for (int i = 0; i < itemCount; i++)
        {
            if (items[i].needsRestock())
            {
                cout << "--------------------" << endl;
                items[i].show();
                found = true;
            }
        }

        if (found == false)
        {
            cout << "No item needs immediate restock by old days-left formula." << endl;
        }
    }

    void showAllRegressionRecommendations() const
    {
        if (itemCount == 0)
        {
            cout << "Inventory is empty. Load files first." << endl;
            return;
        }

        cout << "Regression Based Inventory Prediction and Recommendation" << endl;
        LinearRegressionModel linearModel;
        LogisticRegressionModel logisticModel(-1.60, 1.20, 0.75, 0.30, 1.10, 0.65);
        linearModel.showSixMathematicalFormulas();
        logisticModel.showSixLogisticFormulas();

        for (int i = 0; i < itemCount; i++)
        {
            cout << "--------------------" << endl;
            cout << "Item: " << items[i].getName() << endl;
            cout << "Quantity: " << items[i].getQuantity() << endl;
            cout << "Predicted Tomorrow Use: " << items[i].predictNextDailyUse() << endl;
            cout << "Predicted Days Left: " << items[i].predictedDaysLeft() << endl;
            cout << "Risk Probability: " << items[i].restockRiskProbability() * 100.0 << "%" << endl;
            cout << "Risk Level: " << items[i].restockRiskLevel() << endl;
            cout << "Suggested Order Quantity: " << items[i].suggestedOrderQuantity() << endl;
            cout << "Recommendation: " << items[i].getRecommendation() << endl;
        }
    }

    void showTrees() const
    {
        cout << "AVL item names in order: ";
        itemNameTree.inorder();
        cout << "BST quantities in order: ";
        quantityTree.inorder();
    }

    int countItems() const
    {
        return itemCount;
    }
};

#endif
