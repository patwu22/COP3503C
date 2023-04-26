#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

int main()
{
    cout << "1. Random Numbers\n";
    cout << "2. State Info\n";

    int option;
    cin >> option;

    if (option == 1)
    {
        int randomSeed;
        int times;
        int sides;
        cout << "Random seed value: ";
        cin >> randomSeed;
        random_mt.seed(randomSeed);

        cout << "Number of times to roll the die: ";
        cin >> times;

        cout << "Number of sides on this die: ";
        cin >> sides;

        // Roll Dice
        map<unsigned int, unsigned int> rolls;
        for (int i = 1; i <= sides; i++)
        {
            rolls[i] = 0;
        }
        for (int i = 0; i < times; i++)
        {
            rolls[Random(1, sides)]++;
        }
        cout << "\n";
        for (int i = 1; i <= sides; i++)
        {
            cout << i << ": " << rolls[i] << endl;
        }
    }
    else if (option == 2)
    {
        // Load the states
        map<string, unsigned int[4]> states;
        ifstream fin;
        string line;
        string var;
        fin.open("states.csv");
        if (fin.is_open())
        {
            getline(fin, line);
            while (fin.good())
            {
                getline(fin, line, ',');
                if (line != "")
                {
                    for (int i = 0; i < 3; i++)
                    {
                        getline(fin, var, ',');
                        states[line][i] = stoi(var);
                    }
                    getline(fin, var);
                    states[line][3] = stoi(var);
                }
            }
            // Get input for option 1 (show all states) or 2 (do a search for a particular state)
            cout << "1. Print all states\n";
            cout << "2. Search for a state\n";

            int option2;
            cin >> option2;
            if (option2 == 1)
            {
                for (auto iter = states.begin(); iter != states.end(); iter++)
                {
                    cout << iter->first << endl;
                    cout << "Population: " << iter->second[1] << endl;
                    cout << "Per Capita Income: " << iter->second[0] << endl;
                    cout << "Median Household Income: " << iter->second[2] << endl;
                    cout << "Number of Households: " << iter->second[3] << endl;
                }
            }
            else if (option2 == 2)
            {
                string input;
                cin >> input;
                auto iter = states.find(input);
                if (iter != states.end())
                {
                    cout << iter->first << endl;
                    cout << "Population: " << iter->second[1] << endl;
                    cout << "Per Capita Income: " << iter->second[0] << endl;
                    cout << "Median Household Income: " << iter->second[2] << endl;
                    cout << "Number of Households: " << iter->second[3] << endl;
                }
                else
                {
                    cout << "No match found for " << input << endl;
                }
            }
        }
        else
        {
            cout << "Not open." << endl;
        }
    }
    return 0;
}
