# Snake and Ladder Game in C++ 
A simple implementation of the classic Snake and Ladder game in C++.

This project demonstrates the use of classes, maps, random number generation, and basic game mechanics in C++. The game allows multiple players to roll dice, move across a board, and interact with snakes and ladders.

Features
1. Multiple Players: Supports 2 to 4 players.
Snake and Ladder Mechanics: Includes predefined snake and ladder endpoints.
2. Dice Roll Simulation: Uses rand() to simulate a dice roll between 1 and 6.
3. Game Progress: Tracks the player's position on the board and updates their position based on dice rolls, snake bites, and ladder climbs.
4. Dynamic Player Registration: Players are registered with unique names and their progress is updated until one reaches the end.

Game Rules
1. Players take turns rolling the dice.
2. If a player rolls a 6, they can start from the beginning.
3. Players move forward based on their dice roll.
4. If a player lands on a ladder, they move to the ladder’s top.
5. If a player lands on a snake, they move to the snake's tail.
6. The first player to reach position 100 wins the game.
7. The game continues until a player reaches 100.

Installation
1. Clone the repository to your local machine.
$ git clone git@github.com:pkverma2974/cpp_backend.git

2. Navigate to the project directory.
$ cd snake_ladder

3. Compile the code using any C++ compiler.
$ g++ main.cpp -o snake_and_ladder

4. Run the compiled program.
$ ./snake_and_ladder

How to Play
1. Enter the number of players: You will be prompted to enter the number of players (between 2 and 4).
2. Enter player names: You will be prompted to enter unique names for each player.
3. Start the game: The game will start and players will take turns rolling the dice.
4. Objective: The goal is to reach position 100 by rolling the dice and interacting with snakes and ladders.
