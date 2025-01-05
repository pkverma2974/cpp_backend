# Parking Management System

A simple parking management system implemented in C++ to simulate parking and outing of cars. This system handles cars parking in and out of a parking area and manages waiting cars when the parking area is full. It uses multithreading to monitor the status of cars in the parking system concurrently.

## Features

- Allows parking of cars if there is available space.
- Handles car outings by removing cars from the parking area.
- When the parking area is full, cars are queued and moved to parking when space becomes available.
- Continuous monitoring of car movement (parking and outing) via multithreading.
- Provides an option to display the current status of parked and waiting cars.

## Requirements

- C++11 or later
- Compiler supporting the `<bits/stdc++.h>` header (e.g., GCC)

## Compilation and Execution
1. Compile the program:
    $ g++ -std=c++11 -o parking_system parking_system.cpp -pthread
2. Run the program:
    $ ./parking_system