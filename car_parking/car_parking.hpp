#ifndef CAR_PARKING_HPP
#define CAR_PARKING_HPP
#include <iostream>
#include <map>
#include <thread>
#include <set>
#include <queue>
using namespace std;
/**
 * @brief Class representing a parking system for cars.
 * This class handles the parking and outing of cars, along with monitoring the parking status.
 */
class CarParking
{
private:
    // Maps to store parked cars, their positions, and waiting cars.
    map<int, string> parked_car; // List of cars parked in parking area
    queue<string> waiting_car;   // List of cars waiting outside the parking area
    set<string> parked_check;    // Set for checking duplicates in parked cars
    set<string> waiting_check;   // Set for checking duplicates in waiting cars
    int parking_limits = 0;      // set the limits for car to be parked in parking area
    thread *car;
    // Color constants for better output readability.
    const std::string reset_ = "\033[0m";   // Reset to default color
    const std::string yellow_ = "\033[33m"; // Yellow color for warnings

public:
    /**
     * @brief Constructor to initialize parking system and start the monitoring thread.
     */
    CarParking();

    /**
     * @brief Continuously monitors the movement of cars, either parking or outing.
     * Handles user input for car status, parking, and outing.
     */
    void carMovement();

    /**
     * @brief Parks a car into the parking area.
     * @param plate_no The plate number of the car to park.
     */
    void parkIn(string plate_no);

    /**
     * @brief Removes a car from the parking area.
     * @param plate_no The plate number of the car to remove.
     */
    void parkOut(string plate_no);

    /**
     * @brief Displays the current status of parked and waiting cars.
     */
    void carPosition();

    /**
     * @brief Checks if parking is available for a car to park or if it is already parked.
     * @param type Type of action (1 - Parking, 2 - Outing)
     * @param plate_num The plate number of the car (optional for status checks)
     * @return The parking slot ID if available, or -1 if no available parking.
     */
    int parking_status(int type, string plate_num = "");
};
#endif