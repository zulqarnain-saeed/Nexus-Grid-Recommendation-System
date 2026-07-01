# Nexus Grid Recommendation System

A comprehensive **Data Structures** project developed in **C++** that simulates a **City Emergency Response and Resource Recommendation System**. The application integrates multiple data structures and algorithms to provide intelligent route planning, emergency dispatching, inventory management, citizen search, recommendation generation, and log compression through an interactive command-line interface.

Developed as a **4th Semester Data Structures Project**.

---

## Overview

The **Nexus Grid Recommendation System** demonstrates how various data structures can work together to solve real-world computational problems.

The system loads information from text files and allows users to perform tasks such as finding the shortest route between locations, processing emergency requests based on priority, managing medical inventory, searching citizen records, generating restocking recommendations, and compressing system logs.

Every module is implemented using the most appropriate data structure to ensure efficient data processing and to demonstrate practical applications of Data Structures and Algorithms.

---

# Features

### Emergency Management

* Register emergency requests
* Priority-based emergency dispatch
* Emergency risk score calculation
* Max Heap implementation

### Navigation System

* Display city road network
* Shortest route calculation
* Breadth-First Search (BFS)
* Depth-First Search (DFS)
* Dijkstra-based path finding

### Inventory Management

* Load inventory records
* Search inventory items
* Low stock detection
* Demand prediction
* Resource recommendation

### Citizen Search

* Fast record lookup
* Hash Table implementation
* Search by Citizen ID

### Archive System

* Compress log files
* Restore compressed logs
* Huffman Coding implementation

### File Management

* Read data from text files
* Store system logs
* Persistent data management

### OOP Demonstration

* Base Vehicle class
* Ambulance
* Truck
* Electric Bike
* Inheritance
* Polymorphism

---

# System Architecture

```text
                         +---------------------------+
                         |     System Integrator     |
                         +------------+--------------+
                                      |
        ---------------------------------------------------------------
        |              |               |              |                |
        v              v               v              v                v
+----------------+ +---------------+ +---------------+ +---------------+ +---------------+
|  Navigation    | |  Emergency    | |  Inventory    | |    Search     | |    Archive    |
+----------------+ +---------------+ +---------------+ +---------------+ +---------------+
| Graph          | | Max Heap      | | Dynamic Array | | Hash Table    | | Huffman Tree  |
| Dijkstra       | | Priority Queue| | BST           | | Citizen Search| | Compression   |
| BFS / DFS      | | Queue         | | AVL Tree      | | Item Search   | | Decompression |
+----------------+ +---------------+ +---------------+ +---------------+ +---------------+
```

---

# Data Structures Implemented

| Data Structure           | Purpose                                                |
| ------------------------ | ------------------------------------------------------ |
| Graph                    | City map representation and shortest route calculation |
| Min Heap                 | Dijkstra's shortest path algorithm                     |
| Max Heap                 | Emergency priority scheduling                          |
| Queue                    | Breadth-First Search (BFS)                             |
| Stack                    | Depth-First Search (DFS)                               |
| Circular Queue           | Emergency waiting area rotation                        |
| Hash Table               | Fast citizen and inventory search                      |
| Binary Search Tree (BST) | Sorted inventory records                               |
| AVL Tree                 | Balanced inventory management                          |
| Linked List              | Dynamic node-based storage                             |
| Dynamic Array            | Inventory storage                                      |
| Huffman Tree             | Log compression and decompression                      |

---

# Algorithms Used

* Dijkstra's Shortest Path Algorithm
* Breadth-First Search (BFS)
* Depth-First Search (DFS)
* Huffman Coding
* Hashing
* Tree Traversals
* Heap Operations
* Dynamic Memory Allocation

---

# Project Structure

```text
.
├── main.cpp
├── SystemIntegrator.*
├── Navigation/
│   ├── Graph.*
│   ├── BFS.*
│   ├── DFS.*
│   └── Dijkstra.*
│
├── Emergency/
│   ├── EmergencyDispatcher.*
│   ├── MaxHeap.*
│   └── Queue.*
│
├── Inventory/
│   ├── ResourceManager.*
│   ├── DynamicArray.*
│   ├── BST.*
│   ├── AVL.*
│   └── HashTable.*
│
├── Archive/
│   ├── Huffman.*
│   └── FileHandler.*
│
├── Vehicle/
│   ├── Vehicle.*
│   ├── Ambulance.*
│   ├── Truck.*
│   └── ElectricBike.*
│
├── map.txt
├── inventory.txt
├── demand_history.txt
├── citizens.txt
├── logs.txt
├── compressedLogs.txt
├── restoredLogs.txt
└── README.md
```

---

# Technologies Used

* C++
* Object-Oriented Programming (OOP)
* Standard Template Library (STL)
* File Handling
* Dynamic Memory Allocation
* Command-Line Interface (CLI)

---

# Key Concepts Demonstrated

The project demonstrates practical implementation of:

* Graph Algorithms
* Heaps
* Hash Tables
* Binary Search Trees
* AVL Trees
* Linked Lists
* Queues
* Stacks
* Huffman Coding
* File Handling
* Dynamic Memory Management
* Object-Oriented Programming

---

# Getting Started

## Prerequisites

* C++11 or later
* GCC / G++
* Clang
* Microsoft Visual Studio

---

## Compilation

Compile all source files using:

```bash
g++ -std=c++11 *.cpp -o NexusGrid
```

---

## Run

### Linux / macOS

```bash
./NexusGrid
```

### Windows

```bash
NexusGrid.exe
```

---

# Example Workflow

1. Load project data.
2. Display the city road network.
3. Find the shortest route between two locations.
4. Register emergency requests.
5. Dispatch the highest priority emergency.
6. Search citizen records.
7. Monitor inventory levels.
8. Generate stock recommendations.
9. Compress system logs.
10. Restore compressed log files.

---

# Learning Outcomes

This project demonstrates concepts from:

* Data Structures
* Algorithms
* Object-Oriented Programming
* Graph Theory
* Hashing
* Priority Queues
* Tree Data Structures
* File Handling
* Data Compression
* Software Design

---

# Future Improvements

Potential enhancements include:

* Graphical User Interface (GUI)
* Database Integration
* Live GPS Navigation
* Machine Learning-Based Demand Prediction
* Real-Time Emergency Tracking
* Multi-User Support
* REST API Integration
* Interactive Dashboard

---

# License

This project is intended for educational and academic purposes.

Feel free to fork, modify, and extend the project for learning and research.

---

# Authors

**Zulqarnain Saeed**

Bachelor of Science in Computer Science

**4th Semester Data Structures Project**
