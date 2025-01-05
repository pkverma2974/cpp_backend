#include "car_parking.hpp"
/**
 * @brief Constructor for the parkingCar class.
 * Initializes parking limits and starts the car movement monitoring in a separate thread.
 */
CarParking::CarParking()
{
    string input;
    cout << "Enter parking limits: ";
    while (true)
    {
        cin >> input; // Read the input as a string
        try
        {
            parking_limits = stoi(input); // Try to convert the string to an integer
            if (parking_limits <= 0)
            {
                cout << yellow_ << "Warning: " << "Please enter a number greater than 0!" << reset_ << endl;
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }
        catch (const invalid_argument &e)
        {
            // If stoi throws an invalid_argument exception, input is not a valid number
            cout << yellow_ << "Warning: " << "Enter a valid number!" << reset_ << endl;
        }
        catch (const out_of_range &e)
        {
            // If the number is too large for an int, handle this exception
            cout << yellow_ << "Warning: " << "The number is too large. Please try again!" << reset_ << endl;
        }
        cout << "Enter parking limits: ";
    }

    cout << "Parking limits set to: " << parking_limits << endl;
    // Initialize parking slots as empty.
    for (int i = 0; i < parking_limits; i++)
    {
        parked_car[i] = "";
    }

    cout << "Start parking and outing\n";
    // Create a new thread to monitor car movements.
    car = new thread(&CarParking::carMovement, this);
    // Wait for the thread to finish execution before proceeding.
    if (car->joinable())
    {
        car->join();
    }
}

/**
 * @brief Continuously monitors the user input for parking and outing actions.
 * Provides options for checking car status, parking cars, and outing cars.
 */
void CarParking::carMovement()
{
    cout << "Press Key (status->0, parking->1, outing->2): ";
    int type = 0; // 1 for parking, 2 for outing
    string input;
    while (true)
    {
        cin >> input;
        try
        {
            type = stoi(input);
            string plate_no = "";

            if (type == 0)
            {
                carPosition(); // Display current parking and waiting car status
            }
            else if (type == 1 || type == 2)
            {
                cout << "Enter plate number of car: ";
                cin >> plate_no;

                if (type == 1)
                {
                    parkIn(plate_no); // Park the car
                }
                else if (type == 2)
                {
                    parkOut(plate_no); // Remove the car
                }
            }
            else
            {
                cout << yellow_ << "Warning: " << "Enter a valid number from given range!" << reset_ << endl;
            }
        }
        catch (const std::exception &e)
        {
            cout << yellow_ << "Warning: " << "Enter a valid key!" << reset_ << endl;
        }
        cout << "Press Key (status->0, parking->1, outing->2): ";
    }
}

/**
 * @brief Displays the current parking and waiting car status.
 */
void CarParking::carPosition()
{
    cout << "Parked cars: ";
    for (auto it : parked_car)
    {
        cout << "[" << it.first << ":" << it.second << "],";
    }
    cout << "\nWaiting cars: [";

    // Display all waiting cars in the queue
    queue<string> temp_queue = waiting_car;
    while (!temp_queue.empty())
    {
        cout << temp_queue.front() << ",";
        temp_queue.pop();
    }
    cout << "]" << endl;
}

/**
 * @brief Checks if parking is available for a car, or if the car is already parked.
 * @param type Type of check (1 for parking, 2 for outing)
 * @param plate_num The plate number of the car.
 * @return The parking slot ID if available, or -1 if no available parking.
 */
int CarParking::parking_status(int type, string plate_num)
{
    if (type == 1)
    {
        int parkId_available = -1;
        for (auto it : parked_car)
        {
            if (it.second.empty()) // Check for empty parking slot
            {
                parkId_available = it.first;
                break;
            }
        }
        return parkId_available;
    }
    else if (type == 2)
    {
        int parked_Id = -1;
        for (auto it : parked_car)
        {
            if (it.second == plate_num) // Find the parking slot of the car
            {
                parked_Id = it.first;
                break;
            }
        }
        return parked_Id;
    }
    return -1; // No parking found
}

/**
 * @brief Parks a car in the parking area.
 * If the parking area is full, the car will be added to the waiting list.
 * @param plate_no The plate number of the car to park.
 */
void CarParking::parkIn(string plate_no)
{
    int parkId_available = parking_status(1); // Check for available parking slot

    if (parkId_available == -1)
    {
        if (parked_check.count(plate_no))
        {
            cout << yellow_ << "Warning: " << "Car with Plate Number " + plate_no + " is already in parked area!" << reset_ << endl;
        }
        else if (!waiting_check.count(plate_no))
        {
            cout << "Parking area is full! Please wait...\n";
            waiting_check.insert(plate_no);
            waiting_car.push(plate_no);
        }
        else
        {
            cout << yellow_ << "Warning: " << "Car with Plate Number " + plate_no + " is already in waiting area!" << reset_ << endl;
        }
    }
    else
    {
        if (!parked_check.count(plate_no))
        {
            parked_check.insert(plate_no);
            parked_car[parkId_available] = plate_no; // Assign the car to an available parking slot
        }
        else
        {
            cout << yellow_ << "Warning: " << "Car with Plate Number " + plate_no + " is already parked!" << reset_ << endl;
        }
    }

    carPosition(); // Display the updated parking and waiting status
}

/**
 * @brief Removes a car from the parking area and checks if a waiting car can now park.
 * @param plate_no The plate number of the car to remove.
 */
void CarParking::parkOut(string plate_no)
{
    int parked_Id = parking_status(2, plate_no); // Check if the car is parked

    if (parked_Id == -1)
    {
        cout << yellow_ << "Warning: " << "No car with plate number " + plate_no + " is parked!" << reset_ << endl;
    }
    else
    {
        // Remove the car from the parking area
        auto itr = parked_car.find(parked_Id);
        itr->second = "";
        parked_check.erase(plate_no);
        cout << "Car with plate number " << plate_no << " is now leaving the parking area.\n";
        carPosition(); // Update the parking status

        // Move the first waiting car to the parking area if there's space
        while (!waiting_car.empty() && parking_status(1) != -1)
        {
            string plate_no = waiting_car.front();
            waiting_check.erase(plate_no);
            waiting_car.pop();
            cout << "Car with plate number " + plate_no + " will be parked now!\n";
            parkIn(plate_no);
        }
    }
}

/**
 * @brief Main entry point to start the parking system.
 */
int main()
{
    // Create a new parkingCar object to initialize the system
    CarParking *car_park = new CarParking();
    delete car_park;
    return 0;
}
