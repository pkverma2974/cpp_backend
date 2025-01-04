#include "snake_ladder.hpp"

snake_ladder::snake_ladder(int num)
{
    num_ = num;
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
            cout << "Name should be unique\n";
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
    cout << "Enter number of players: ";
    int num = 0;
    cin >> num;
    while (num < 2 || num > 4)
    {
        cout << "Number of player should be at least 2 and max 4\n";
        cin >> num;
    }

    snake_ladder sn_lad_obj(num);
    sn_lad_obj.snake_end_point();
    sn_lad_obj.ladder_end_point();
    cout << "snake & ladder map created\n";

    sn_lad_obj.players_detail();
    string winner_ = sn_lad_obj.start_game();

    cout << "Winner of the Match is " << winner_ << "\n";
    cout << "current status\n";
    for (auto it : sn_lad_obj.players_map)
    {
        cout << it.first << "->" << it.second << " ";
    }

    return 0;
}