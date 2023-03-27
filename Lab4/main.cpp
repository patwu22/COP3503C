#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
    int option;
    cin >> option;

    /* Load files here */
    vector<ship> ships;
    int num;
    if (option == 1 || option == 3)
    {
        ifstream fin1("friendlyships.shp");
        fin1.read((char *)&num, 4);
        for (int i = 0; i < num; i++)
        {
            ships.push_back(loadship(fin1));
        }
        fin1.close();
    }
    if (option == 2 || option == 3)
    {
        ifstream fin2("enemyships.shp");
        fin2.read((char *)&num, 4);
        for (int i = 0; i < num; i++)
        {
            ships.push_back(loadship(fin2));
        }
        fin2.close();
    }

    cin >> option;

    if (option == 1)
    {
        for (int i = 0; i < (int)ships.size(); i++)
        {
            ships[i].print();
        }
    }
    else if (option == 2)
    {
        int pfship = 0;
        for (int i = 0; i < (int)ships.size(); i++)
        {
            if (ships[i].pfweapon() > ships[pfship].pfweapon())
                pfship = i;
        }
        ships[pfship].print();
    }
    else if (option == 3)
    {
        int fpship = 0;
        for (int i = 0; i < (int)ships.size(); i++)
        {
            if (ships[i].firepower() > ships[fpship].firepower())
                fpship = i;
        }
        ships[fpship].print();
    }
    else if (option == 4)
    {
        int fpship = 0;
        for (int i = 0; i < (int)ships.size(); i++)
        {
            if (ships[fpship].firepower() == 0)
                fpship += 1;
            if (ships[i].firepower() < ships[fpship].firepower() && ships[i]._numweapon != 0)
                fpship = i;
        }
        ships[fpship].print();
    }
    else if (option == 5)
    {
        for (int i = 0; i < (int)ships.size(); i++)
        {
            if (ships[i]._numweapon == 0)
                ships[i].print();
        }
    }

    return 0;
}
