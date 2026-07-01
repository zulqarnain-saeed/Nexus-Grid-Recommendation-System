Nexus Grid Recommendation System

A comprehensive Data Structures project developed in C++ that simulates a city emergency response and resource management system. The project integrates multiple data structures and algorithms to solve real-world problems such as route optimization, emergency dispatching, inventory management, citizen search, and log compression through an interactive command-line interface.

Developed as a 4th Semester Data Structures Project.

Project Overview

The Nexus Grid Recommendation System demonstrates how different data structures can work together within a single application.

The system loads data from text files and provides various modules for emergency management, route planning, inventory monitoring, citizen search, and recommendation generation. Each module utilizes the most suitable data structure to ensure efficient operations.

The project focuses on practical implementation of fundamental data structures and algorithms rather than theoretical demonstrations.

Features
Emergency Management
Add emergency requests
Process emergencies based on priority
Calculate emergency risk score
Priority-based emergency dispatching using Max Heap
Route Navigation
Display city road network
Find shortest path between locations
Breadth-First Search (BFS)
Depth-First Search (DFS)
Dijkstra-style shortest path algorithm
Inventory Management
Load inventory records
Search inventory items
Detect low stock
Predict future demand
Generate restocking recommendations
Citizen Search
Fast citizen lookup
Hash Table implementation
Search by citizen ID
File Handling
Load project data from text files
Read and write system logs
Persistent data storage
Log Compression
Huffman Encoding
Log compression
Log decompression
OOP Demonstration
Base Vehicle class
Ambulance
Truck
Electric Bike
Inheritance
Polymorphism
Data Structures Implemented

The project demonstrates practical implementation of the following data structures:

Data Structure	Purpose
Graph	City map and road network
Min Heap	Shortest route calculation
Max Heap	Emergency priority queue
Queue	Breadth-First Search (BFS)
Stack	Depth-First Search (DFS)
Circular Queue	Emergency waiting areas
Hash Table	Fast citizen and inventory search
Binary Search Tree (BST)	Sorted inventory records
AVL Tree	Balanced inventory storage
Dynamic Array	Inventory management
Linked List	Data structure demonstrations
Huffman Tree	Log compression
Algorithms Used
Dijkstra's Shortest Path Algorithm
Breadth-First Search (BFS)
Depth-First Search (DFS)
Huffman Coding
Hashing
Priority Queue Operations
Tree Traversals
Dynamic Memory Allocation
System Modules
                   +----------------------+
                   |   System Integrator  |
                   +----------+-----------+
                              |
      ------------------------------------------------
      |            |            |            |        |
      v            v            v            v        v
 Navigation   Emergency   Inventory   Search   Archive
      |            |            |            |        |
      v            v            v            v        v
   Graph       Max Heap    Hash Table   Hash Table Huffman
   Min Heap    Queue       BST & AVL               Coding
Project Structure
.
├── main.cpp
├── SystemIntegrator.*
├── Graph.*
├── MinHeap.*
├── MaxHeap.*
├── EmergencyDispatcher.*
├── ResourceManager.*
├── HashTable.*
├── BST.*
├── AVL.*
├── Queue.*
├── Stack.*
├── LinkedList.*
├── Huffman.*
├── FileHandler.*
├── Vehicle.*
├── Ambulance.*
├── Truck.*
├── ElectricBike.*
├── map.txt
├── inventory.txt
├── citizens.txt
├── demand_history.txt
├── logs.txt
├── compressedLogs.txt
├── restoredLogs.txt
└── README.md
Technologies Used
C++
Object-Oriented Programming (OOP)
Standard Template Library (STL)
File Handling
Dynamic Memory Allocation
Command-Line Interface (CLI)
Key Concepts Demonstrated
Data Structures
Algorithms
Object-Oriented Programming
File Handling
Graph Traversal
Route Optimization
Priority Scheduling
Hashing
Data Compression
Resource Management
Getting Started
Prerequisites
C++11 or later
GCC / G++ / Clang / MSVC
Compile
g++ -std=c++11 *.cpp -o NexusGrid
Run
Linux / macOS
./NexusGrid
Windows
NexusGrid.exe
Example Workflow
Load project data.
Display city map.
Find the shortest route.
Add emergency requests.
Process highest-priority emergency.
Search citizen records.
Manage inventory.
Generate stock recommendations.
Compress system logs.
Restore compressed logs.
Learning Outcomes

This project demonstrates practical implementation of:

Graphs
Heaps
Hash Tables
Binary Search Trees
AVL Trees
Linked Lists
Queues
Stacks
Huffman Coding
File Handling
Dynamic Memory Management
Object-Oriented Programming
Future Improvements
Graphical User Interface (GUI)
Database Integration
Real-Time GPS Navigation
Machine Learning Based Demand Prediction
Multi-User Support
REST API Integration
Live Emergency Tracking
Interactive Dashboard
License

This project is developed for educational and academic purposes.

Feel free to fork, modify, and extend the project for learning and research.

Authors

Zulqarnain Saeed

Bachelor of Science in Computer Science

4th Semester Data Structures Project
