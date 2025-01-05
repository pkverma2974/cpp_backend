#include "snake_ladder.hpp"

snake_ladder::snake_ladder()
{
    int num = 0;
    string input;
    while (true)
    {
        cout << "Enter number of players: ";
        cin >> input;
        // Validate that the input contains only digits
        if (isValidNumber(input))
        {
            num = stoi(input);
            if (num >= 2 && num <= 4)
            {
                break; // Valid input, break the loop
            }
            else
            {
                cout << yellow_ << "WARNING: " << "Number of players should be at least 2 and max 4" << reset_ << endl;
            }
        }
        else
        {
            cout << yellow_ << "WARNING: " << "Enter a valid number of players (no letters or symbols allowed)!" << reset_ << endl;
        }
    }
    num_ = num;
}

bool snake_ladder::isValidNumber(string input)
{
    // Check if all characters in the input string are digits
    for (char ch : input)
    {
        if (!isdigit(ch))
        {
            return false; // Return false if any character is not a digit
        }
    }
    return true;
}

void snake_ladder::snake_end_point()
{
    snake_map.insert({27, 3});
    snake_map.insert({49, 19});
    snake_map.insert({55, 35});
    snake_map.insert({67, 51});
    snake_map.insert({81, 47});
    snake_map.insert({99, 41});
}

void snake_ladder::ladder_end_point()
{
    ladder_map.insert({8, 22});
    ladder_map.insert({20, 42});
    ladder_map.insert({34, 54});
    ladder_map.insert({52, 70});
    ladder_map.insert({68, 88});
    ladder_map.insert({82, 96});
}

void snake_ladder::players_detail()
{
    int i = 0;
    while (i < num_)
    {
        cout << "Enter player name: ";
        string name;
        cin >> name;
        if (players_map.find(name) == players_map.end())
        {
            players_map.insert({name, 0});
            i++;
        }
        else
        {
            cout << yellow_ << "WARNING: " << "Name should be unique" << reset_ << endl;
        }
    }
    cout << "Players name registered\n";
}

int snake_ladder::roll_dice()
{
    int min_ = 1;
    int max_ = 6;
    srand(time(0));
    int rolled_ = min_ + rand() % (max_ - min_ + 1);
    return rolled_;
}

string snake_ladder::start_game()
{
    while (true)
    {
        auto it = players_map.begin();
        for (int i = 0; i < num_; i++)
        {
            cout << "roll the dice by " << it->first << "->";
            string str;
            cin >> str;
            int roll_val = roll_dice();
            if (it->second == 0) // Home
            {
                if (roll_val == 6) // started
                {
                    players_map[it->first] = 1;
                }
            }
            else
            {
                int total = it->second + roll_val;
                if (total <= 100)
                {
                    if (ladder_map.find(total) != ladder_map.end())
                    {
                        auto lad_itr = ladder_map.find(total);
                        players_map[it->first] = lad_itr->second;
                        cout << "found ladder with val: " << lad_itr->second << "\n";
                    }
                    else if (snake_map.find(total) != snake_map.end())
                    {
                        auto sna_itr = snake_map.find(total);
                        players_map[it->first] = sna_itr->second;
                        cout << "snake ladder with val: " << sna_itr->second << "\n";
                    }
                    else
                    {
                        players_map[it->first] = total;
                        if (total == 100)
                        {
                            return it->first;
                        }
                    }
                }
            }

            it++;
        }
        cout << "Current score\n";
        for (auto it : players_map)
        {
            cout << it.first << "->" << it.second << " ";
        }
        cout << "\n";
    }
}

int main()
{
    snake_ladder sn_lad_obj;
    cout << "Number of players: " << sn_lad_obj.num_ << endl;
    sn_lad_obj.snake_end_point();
    sn_lad_obj.ladder_end_point();
    cout << "snake & ladder map created\n";

    sn_lad_obj.players_detail();
    cout << "Starting the game!\n";
    string winner_ = sn_lad_obj.start_game();

    cout << sn_lad_obj.yellow_ << "INFO: " << "Winner of the Match is " << winner_ << sn_lad_obj.reset_ << endl;
    cout << "current status\n";
    for (auto it : sn_lad_obj.players_map)
    {
        cout << it.first << "->" << it.second << " ";
    }

    return 0;
}