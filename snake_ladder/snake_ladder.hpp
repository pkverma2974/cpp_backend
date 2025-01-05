#ifndef SNAKE_LADDER_HPP
#define SNAKE_LADDER_HPP
#include <iostream>
#include <unordered_map>
using namespace std;

class snake_ladder
{
private:
    unordered_map<int, int> snake_map;  // it contains the snake end and starting point
    unordered_map<int, int> ladder_map; // it contains the ladder starting and end point

public:
    /*!
     * \param num_: The number of players in the game. It is used to set up the game
     *            board and initialize the required structures for the players.
     */
    int num_;
    unordered_map<string, int> players_map; // it contains the players and their respective position
    // Color constants for better output readability.
    const std::string reset_ = "\033[0m";   // Reset to default color
    const std::string yellow_ = "\033[33m"; // Yellow color for warnings
    /*!
     * \brief Constructor for the Snake and Ladder game.
     */
    snake_ladder();
    /*!
     * \brief Checks if the input string contains only numeric digits.
     * \param input The string to be validated.
     * \return Returns true if the input contains only digits, false otherwise.
     */
    bool isValidNumber(string input);
    /*!
     * \brief Calculates the end point of a snake on the game board.
     *
     * This function identifies where the snake ends (i.e., where the player
     * would land after stepping on the snake's head).
     */
    void snake_end_point();
    /*!
     * \brief Calculates the end point of a ladder on the game board.
     *
     * This function determines where a player would land after stepping on the bottom of a ladder.
     * When a player encounters the base of a ladder, they are moved to the top of the ladder.     */
    void ladder_end_point();
    /*!
     * \brief Displays the details of all players in the game.
     *
     * This function contains information about each player,and initiaze the current position with Home.
     */
    void players_detail();
    /*!
     * \brief Initiates the Snake and Ladder game.
     *
     * This function manages the core gameplay by allowing each player to take turns rolling the dice.
     * Based on the dice roll, players' positions on the board are updated, and they move accordingly.
     * The game continues until a player reaches the final square and wins.
     *
     * \return A string message indicating the result of the winner name.
     */
    string start_game();
    /*!
     * \brief Simulates the rolling of a dice.
     *
     * This function generates a random integer between 1 and 6, inclusive, simulating the roll of a standard six-sided dice.
     * The result can then be used to determine the number of spaces a player moves forward in the game.
     *
     * \return A random integer between 1 and 6, representing the dice roll.
     */
    int roll_dice();
};
#endif