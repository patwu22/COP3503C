#pragma once
#include <random>

struct core
{
    unsigned int _columns;
    unsigned int _rows;
    unsigned int _num_mines;
    int *tiles = nullptr;
    int *mines = nullptr;
    bool *flags = nullptr;

    core(unsigned int columns, unsigned int rows, unsigned int num_mines)
    {
        _columns = columns;
        _rows = rows;
        _num_mines = num_mines;
        tiles = new int[_columns * _rows];
        mines = new int[_columns * _rows];
        flags = new bool[_columns * _rows];
    }

    void setMines()
    {
        for (int i = 0; i < _columns * _rows; i++)
            mines[i] = 0;
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, _columns * _rows - 1);
        int count = 0;
        while (count < _num_mines)
        {
            int m = dist(rng);
            if (mines[m] == 0)
            {
                mines[m] = 1;
                count++;
            }
        }
    }

    unsigned int onclick_left(int x, int y)
    {
        if (flags[x + _columns * y] == 1)
            return 0;
        if (tiles[x + _columns * y] == 0 && mines[x + _columns * y] == 0)
        {
            int mine_count = 0;
            if (x != 0)
                mine_count += mines[x + _columns * y - 1];
            if (x != _columns - 1)
                mine_count += mines[x + _columns * y + 1];
            if (y != 0)
                mine_count += mines[x + _columns * y - _columns];
            if (y != _rows - 1)
                mine_count += mines[x + _columns * y + _columns];
            if (x != 0 && y != 0)
                mine_count += mines[x + _columns * y - _columns - 1];
            if (x != 0 && y != _rows - 1)
                mine_count += mines[x + _columns * y + _columns - 1];
            if (x != _columns - 1 && y != 0)
                mine_count += mines[x + _columns * y - _columns + 1];
            if (x != _columns - 1 && y != _rows - 1)
                mine_count += mines[x + _columns * y + _columns + 1];

            if (mine_count == 0)
            {
                tiles[x + _columns * y] = 1;
                if (x != 0)
                    onclick_left(x - 1, y);
                if (x != _columns - 1)
                    onclick_left(x + 1, y);
                if (y != 0)
                    onclick_left(x, y - 1);
                if (y != _rows - 1)
                    onclick_left(x, y + 1);
                if (x != 0 && y != 0)
                    onclick_left(x - 1, y - 1);
                if (x != 0 && y != _rows - 1)
                    onclick_left(x - 1, y + 1);
                if (x != _columns - 1 && y != 0)
                    onclick_left(x + 1, y - 1);
                if (x != _columns - 1 && y != _rows - 1)
                    onclick_left(x + 1, y + 1);
            }
            else
                tiles[x + _columns * y] = mine_count - 11;
            if (vic_check())
                return 2;
        }
        else if (tiles[x + _columns * y] == 0 && mines[x + _columns * y] == 1)
        {
            for (int i = 0; i < _columns * _rows; i++)
                if (mines[i] == 1)
                    tiles[i] = 1;
            return 1;
        }
        return 0;
    }

    bool vic_check()
    {
        int tile_count = 0;
        for (int i = 0; i < _columns * _rows; i++)
        {
            if (tiles[i] == 0 && mines[i] == 0)
                tile_count++;
        }
        if (tile_count == 0)
            return true;
        return false;
    }

    void onclick_right(int x, int y)
    {
        if (tiles[x + _columns * y] == 0)
        {
            if (flags[x + _columns * y])
                flags[x + _columns * y] = false;
            else
                flags[x + _columns * y] = true;
        }
    }

    ~core()
    {
        delete[] tiles;
        tiles = nullptr;
        delete[] mines;
        mines = nullptr;
        delete[] flags;
        flags = nullptr;
    }
};
