#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct ship
{
    struct weapon
    {
        string _name;
        int _power;
        float _consump;
    };
    string _name;
    string _class;
    int _length;
    int _capacity;
    float _speed;
    int _numweapon;
    vector<weapon> _weapon;

    void print()
    {
        cout << "Name: " << _name << endl;
        cout << "Class: " << _class << endl;
        cout << "Length: " << _length << endl;
        cout << "Shield capacity: " << _capacity << endl;
        cout << "Maximum Warp: " << _speed << endl;
        cout << "Armaments:" << endl;
        if (_numweapon == 0)
        {
            cout << "Unarmed" << endl;
        }
        else
        {
            int total = 0;
            for (int i = 0; i < _numweapon; i++)
            {
                cout << _weapon[i]._name << ", " << _weapon[i]._power << ", " << _weapon[i]._consump << endl;
                total += _weapon[i]._power;
            }
            cout << "Total firepower: " << total << endl;
        }
        cout << endl;
    }

    int pfweapon()
    {
        int pf = 0;
        for (int i = 0; i < _numweapon; i++)
        {
            if (_weapon[i]._power > pf)
                pf = _weapon[i]._power;
        }
        return pf;
    }

    int firepower()
    {
        int fp = 0;
        for (int i = 0; i < _numweapon; i++)
        {
            fp += _weapon[i]._power;
        }
        return fp;
    }
};

void readint(ifstream &fin, int &var)
{
    fin.read((char *)&var, 4);
}

void readchars(ifstream &fin, char *&data, int &length)
{
    fin.read(data, length);
}

ship loadship(ifstream &fin)
{
    ship newship;
    int len;
    float flo;
    char *ptr = nullptr;

    readint(fin, len);
    ptr = new char[len];
    readchars(fin, ptr, len);
    newship._name = (string)ptr;
    delete[] ptr;

    readint(fin, len);
    ptr = new char[len];
    readchars(fin, ptr, len);
    newship._class = (string)ptr;
    delete[] ptr;

    fin.read((char *)&len, 2);
    newship._length = len;
    readint(fin, len);
    newship._capacity = len;
    fin.read((char *)&flo, 4);
    newship._speed = flo;
    readint(fin, len);
    newship._numweapon = len;

    ship::weapon newweapon;
    for (int i = 0; i < newship._numweapon; i++)
    {
        readint(fin, len);
        ptr = new char[len];
        readchars(fin, ptr, len);
        newweapon._name = (string)ptr;
        delete[] ptr;

        readint(fin, len);
        newweapon._power = len;
        fin.read((char *)&flo, 4);
        newweapon._consump = flo;

        newship._weapon.push_back(newweapon);
    }

    return newship;
}
