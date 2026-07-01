#pragma once 
#include <iostream>
#include <string>
#include "DynamicArray.h"
#include "Stack.h"
#include "Queue.h"
#include "CircularQueue.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "CircularLinkedList.h"
#include "Vehicle.h"
#include "Citizen.h"
#include "HashTable.h"
#include "BST.h"
#include "AVL.h"
#include "FileHandler.h"
#include "NavigationSystem.h"
#include "ResourceManager.h"
#include "EmergencyDispatcher.h"
#include "ArchiveSystem.h"
using namespace std;
class SystemIntegrator
{
private:
    static const int STUDENT_INT_MAX = 2147483647;
    static const int STUDENT_INT_MIN = -2147483647 - 1;
    FileHandler fileHandler;
    NavigationSystem navigationSystem;
    ResourceManager resourceManager;
    EmergencyDispatcher emergencyDispatcher;
    ArchiveSystem archiveSystem;
    HashTable<Citizen> citizens;
    bool isBlank(string text) const
    {
        if (text.length() == 0)
        {
            return true;
        }
        for (int i = 0; i < (int)text.length(); i++)
        {
            if (text[i] != ' ' && text[i] != '\t' && text[i] != '\n' && text[i] != '\r')
            {
                return false;
            }
        }

        return true;
    }
    string trim(string text) const
    {
        int start = 0;
        int end = (int)text.length() - 1;

        while (start <= end && (text[start] == ' ' || text[start] == '\t'))
        {
            start++;
        }

        while (end >= start && (text[end] == ' ' || text[end] == '\t'))
        {
            end--;
        }

        string result = "";

        for (int i = start; i <= end; i++)
        {
            result += text[i];
        }

        return result;
    }

    bool toInt(string text, int& number) const
    {
        text = trim(text);

        if (text == "")
        {
            return false;
        }
        int sign = 1;
        int index = 0;

        if (text[0] == '-')
        {
            sign = -1;
            index = 1;
        }
        else if (text[0] == '+')
        {
            index = 1;
        }

        if (index >= (int)text.length())
        {
            return false;
        }

        long long value = 0;
        for (int i = index; i < (int)text.length(); i++)
        {
            if (text[i] < '0' || text[i] > '9')
            {
                return false;
            }

            value = (value * 10) + (text[i] - '0');

            if (value > STUDENT_INT_MAX)
            {
                return false;
            }
        }

        value = value * sign;

        if (value < STUDENT_INT_MIN || value > STUDENT_INT_MAX)
        {
            return false;
        }
        number = (int)value;
        return true;
    }

    int getIntInRange(string message, int minValue, int maxValue)
    {
        string input;
        int value;
        while (true)
        {
            cout << message;
            getline(cin, input);

            if (toInt(input, value) == false)
            {
                cout << "Invalid input. Enter numbers only." << endl;
                continue;
            }

            if (value < minValue || value > maxValue)
            {
                cout << "Wrong input. Enter value from " << minValue << " to " << maxValue << "." << endl;
                continue;
            }

            return value;
        }
    }
    string getText(string message)
    {
        string text;

        while (true)
        {
            cout << message;
            getline(cin, text);
            text = trim(text);

            if (isBlank(text))
            {
                cout << "Input cannot be empty." << endl;
                continue;
            }

            return text;
        }
    }

    void pressEnter()
    {
        string temp;
        cout << "Press Enter to continue----";
        getline(cin, temp);
    }

    void showHeader(string title)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << title << endl;
        cout << "========================================" << endl;
    }

    void loadDataFiles()
    {
        showHeader("LOAD DATA FILES");
        fileHandler.loadMap("Data/map.txt", navigationSystem.getGraph());
        resourceManager.loadFromFile("Data/inventory.txt");
        resourceManager.loadDemandHistoryFromFile("Data/demand_history.txt");
        fileHandler.loadCitizens("Data/citizens.txt", citizens);
        fileHandler.appendLog("Data/logs.txt", "Data files loaded in system.");
    }

    void showVehicles()
    {
        showHeader("OOP VEHICLE DEMO");
        Ambulance ambulance("AMB-01", "Hospital", 90, 2);
        Truck truck("TRK-01", "Warehouse", 55, 3000);
        ElectricBike bike("EBK-01", "Central", 45, 86);
        Vehicle* vehicles[3];
        vehicles[0] = &ambulance;
        vehicles[1] = &truck;
        vehicles[2] = &bike;

        for (int i = 0; i < 3; i++)
        {
            cout << "--------------------" << endl;
            vehicles[i]->showInfo();
            vehicles[i]->move();
        }
    }

    void addEmergencyMenu()
    {
        showHeader("ADD EMERGENCY");
        navigationSystem.showLocations();

        string location = getText("Enter emergency location: ");
        int severity = getIntInRange("Enter severity from 1 to 10: ", 1, 10);
        int waitingTime = getIntInRange("Enter waiting time in minutes from 0 to 1000: ", 0, 1000);

        if (navigationSystem.getGraph().countVertices() > 0 && navigationSystem.getGraph().hasVertex(location) == false)
        {
            cout << "Warning: this location is not present in map. Emergency is still saved." << endl;
        }

        if (emergencyDispatcher.addEmergency(location, severity, waitingTime))
        {
            string logMessage = "Emergency added at " + location + ".";
            fileHandler.appendLog("Data/logs.txt", logMessage);
        }
    }

    void processEmergencyMenu()
    {
        showHeader("PROCESS HIGHEST PRIORITY EMERGENCY");
        emergencyDispatcher.processEmergency("Data/logs.txt");
    }

    void routeMenu()
    {
        int choice = -1;

        while (choice != 0)
        {
            showHeader("NAVIGATION MENU");
            cout << "1. Show map" << endl;
            cout << "2. Find fastest route" << endl;
            cout << "3. BFS traversal" << endl;
            cout << "4. DFS traversal" << endl;
            cout << "0. Back" << endl;

            choice = getIntInRange("Enter choice: ", 0, 4);
            if (choice == 1)
            {
                navigationSystem.showMap();
            }
            else if (choice == 2)
            {
                navigationSystem.showLocations();
                string source = getText("Enter source: ");
                string destination = getText("Enter destination: ");
                navigationSystem.findFastestRoute(source, destination);
            }
            else if (choice == 3)
            {
                navigationSystem.showLocations();
                string source = getText("Enter start location: ");
                navigationSystem.showBfs(source);
            }
            else if (choice == 4)
            {
                navigationSystem.showLocations();
                string source = getText("Enter start location: ");
                navigationSystem.showDfs(source);
            }
        }
    }
    void inventoryMenu()
    {
        int choice = -1;
        while (choice != 0)
        {
            showHeader("INVENTORY MENU");
            cout << "1. Show all inventory" << endl;
            cout << "2. Search inventory item" << endl;
            cout << "3. Add or update inventory item" << endl;
            cout << "4. Show restock warnings" << endl;
            cout << "5. Regression prediction for one item" << endl;
            cout << "6. Show all regression recommendations" << endl;
            cout << "7. Show AVL and BST output" << endl;
            cout << "0. Back" << endl;
            choice = getIntInRange("Enter choice: ", 0, 7);
            if (choice == 1)
            {
                resourceManager.showAll();
            }
            else if (choice == 2)
            {
                string name = getText("Enter item name: ");
                resourceManager.showItem(name);
            }
            else if (choice == 3)
            {
                string name = getText("Enter item name without spaces: ");
                int quantity = getIntInRange("Enter quantity from 0 to 100000: ", 0, 100000);
                int dailyUse = getIntInRange("Enter daily use from 1 to 10000: ", 1, 10000);
                int threshold = getIntInRange("Enter threshold days from 0 to 365: ", 0, 365);

                if (resourceManager.addItem(name, quantity, dailyUse, threshold))
                {
                    cout << "Item saved successfully." << endl;
                    fileHandler.appendLog("Data/logs.txt", "Inventory item saved: " + name);
                }
                else
                {
                    cout << "Item was not saved." << endl;
                }
            }
            else if (choice == 4)
            {
                resourceManager.showLowStock();
            }
            else if (choice == 5)
            {
                string name = getText("Enter item name: ");
                resourceManager.showRegressionForItem(name);
            }
            else if (choice == 6)
            {
                resourceManager.showAllRegressionRecommendations();
            }
            else if (choice == 7)
            {
                resourceManager.showTrees();
            }
        }
    }

    void searchMenu()
    {
        int choice = -1;

        while (choice != 0)
        {
            showHeader("SEARCH MENU");
            cout << "1. Search citizen by ID" << endl;
            cout << "2. Search inventory by name" << endl;
            cout << "0. Back" << endl;
            choice = getIntInRange("Enter choice: ", 0, 2);

            if (choice == 1)
            {
                string id = getText("Enter citizen ID: ");
                Citizen citizen;

                if (citizens.search(id, citizen))
                {
                    citizen.show();
                }
                else
                {
                    cout << "Citizen not found." << endl;
                }
            }
            else if (choice == 2)
            {
                string name = getText("Enter item name: ");
                resourceManager.showItem(name);
            }
        }
    }

    void linkedListTest()
    {
        showHeader("LINKED LIST TEST");

        SinglyLinkedList<int> singleList;
        singleList.insertAtEnd(10);
        singleList.insertAtEnd(20);
        singleList.insertAtEnd(30);
        singleList.insertAtStart(5);
        cout << "Singly linked list: ";
        singleList.display();
        cout << "Deleting 20: ";

        if (singleList.deleteValue(20))
        {
            cout << "Deleted" << endl;
        }
        else
        {
            cout << "Not found" << endl;
        }

        cout << "After delete: ";
        singleList.display();

        DoublyLinkedList<string> doubleList;
        doubleList.insertAtEnd("North");
        doubleList.insertAtEnd("East");
        doubleList.insertAtEnd("South");
        doubleList.insertAtEnd("West");
        cout << "Doubly list forward: ";
        doubleList.displayForward();
        cout << "Doubly list backward: ";
        doubleList.displayBackward();

        CircularLinkedList<string> signalList;
        signalList.insert("Red");
        signalList.insert("Green");
        signalList.insert("Yellow");
        cout << "Circular signal list: ";
        signalList.display();

        string signal;

        for (int i = 0; i < 5; i++)
        {
            if (signalList.moveNext(signal))
            {
                cout << "Signal turn " << i + 1 << ": " << signal << endl;
            }
        }
    }

    void coreStructureTest()
    {
        showHeader("CORE STRUCTURE TEST");

        DynamicArray<int> array;
        array.add(11);
        array.add(22);
        array.add(33);
        cout << "Dynamic array: ";
        array.display();

        Stack<int> stack;
        stack.push(5);
        stack.push(10);
        stack.push(15);
        int stackValue;
        cout << "Stack pop: ";

        while (stack.pop(stackValue))
        {
            cout << stackValue << " ";
        }

        cout << endl;

        Queue<string> queue;
        queue.enqueue("CitizenA");
        queue.enqueue("CitizenB");
        queue.enqueue("CitizenC");
        string queueValue;
        cout << "Queue dequeue: ";

        while (queue.dequeue(queueValue))
        {
            cout << queueValue << " ";
        }

        cout << endl;

        CircularQueue<string> circularQueue(3);
        circularQueue.enqueue("Red");
        circularQueue.enqueue("Green");
        circularQueue.enqueue("Yellow");
        cout << "Circular queue rotations: ";

        for (int i = 0; i < 5; i++)
        {
            string value;

            if (circularQueue.rotate(value))
            {
                cout << value << " ";
            }
        }

        cout << endl;
    }

    void treeAndHashTest()
    {
        showHeader("BST AVL HASH TEST");

        BST<int> bst;
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        cout << "BST inorder: ";
        bst.inorder();

        AVL<int> avl;
        avl.insert(10);
        avl.insert(20);
        avl.insert(30);
        avl.insert(40);
        avl.insert(50);
        cout << "AVL inorder: ";
        avl.inorder();

        HashTable<string> table;
        table.insert("C001", "Ali");
        table.insert("C002", "Sara");
        string name;

        if (table.search("C002", name))
        {
            cout << "Hash search C002: " << name << endl;
        }
        else
        {
            cout << "Hash value not found." << endl;
        }
    }

    void compressMenu()
    {
        showHeader("COMPRESS LOGS");
        archiveSystem.compressLogs("Data/logs.txt", "Data/compressedLogs.txt");
    }

    void decompressMenu()
    {
        showHeader("DECOMPRESS LOGS");
        archiveSystem.decompressLogs("Data/compressedLogs.txt", "Data/restoredLogs.txt");
    }

public:
    void startSystem()
    {
        int choice = -1;

        while (choice != 0)
        {
            showHeader("NEXUS-GRID System");
            cout << "1. Load data files" << endl;
            cout << "2. Show vehicles" << endl;
            cout << "3. Add emergency" << endl;
            cout << "4. Process highest priority emergency" << endl;
            cout << "5. Navigation system" << endl;
            cout << "6. Inventory system" << endl;
            cout << "7. Search citizen or inventory" << endl;
            cout << "8. Test linked lists" << endl;
            cout << "9. Test core structures" << endl;
            cout << "10. Test BST AVL HashTable" << endl;
            cout << "11. Compress logs" << endl;
            cout << "12. Decompress logs" << endl;
            cout << "13. Rotate waiting emergency area" << endl;
            cout << "14. Regression prediction and recommendations" << endl;
            cout << "0. Exit" << endl;

            choice = getIntInRange("Enter choice: ", 0, 14);

            if (choice == 1)
            {
                loadDataFiles();
            }
            else if (choice == 2)
            {
                showVehicles();
            }
            else if (choice == 3)
            {
                addEmergencyMenu();
            }
            else if (choice == 4)
            {
                processEmergencyMenu();
            }
            else if (choice == 5)
            {
                routeMenu();
            }
            else if (choice == 6)
            {
                inventoryMenu();
            }
            else if (choice == 7)
            {
                searchMenu();
            }
            else if (choice == 8)
            {
                linkedListTest();
            }
            else if (choice == 9)
            {
                coreStructureTest();
            }
            else if (choice == 10)
            {
                treeAndHashTest();
            }
            else if (choice == 11)
            {
                compressMenu();
            }
            else if (choice == 12)
            {
                decompressMenu();
            }
            else if (choice == 13)
            {
                emergencyDispatcher.rotateWaitingArea();
            }
            else if (choice == 14)
            {
                showHeader("REGRESSION PREDICTION AND RECOMMENDATION");
                resourceManager.showAllRegressionRecommendations();
            }

            if (choice != 0)
            {
                pressEnter();
            }
        }
        cout << "Program closed safely." << endl;
        cout << "Bye Bye!" << endl;
    }
};


