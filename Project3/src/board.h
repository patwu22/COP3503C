#pragma once
#include "window.h"
#include <fstream>

struct ranking
{
    string name;
    int duration;

    ranking()
    {
        name = "";
        duration = 0;
    }
    ranking(string n, int i)
    {
        name = n;
        duration = i;
    }
    void load(string n, int i)
    {
        name = n;
        duration = i;
    }
};

class board : public window
{
    unsigned int _width;
    unsigned int _height;
    string _path;
    ranking _rank[5];
    sf::Text texts[2];
    sf::RenderWindow w;
    sf::Font font;

public:
    board(unsigned int columns, unsigned int rows, string path, string username)
    {
        index = 2;
        _width = columns * 16;
        _height = rows * 16 + 50;
        _username = username;
        _path = path;

        ifstream fin;
        fin.open(_path + "files/leaderboard.txt");
        string str;
        for (int i = 0; i < 5; i++)
        {
            getline(fin, str);
            _rank[i].load(str.substr(str.find(',') + 1), stoi(str.substr(0, str.find(':'))) * 60 + stoi(str.substr(str.find(':') + 1, str.find(','))));
        }
        fin.close();

        font.loadFromFile(_path + "files/font.ttf");

        texts[0].setString("LEADERBOARD");
        texts[0].setFont(font);
        texts[0].setCharacterSize(20);
        texts[0].setStyle(sf::Text::Underlined | sf::Text::Bold);
        texts[0].setPosition(centeringText(texts[0], _width / 2.0f, _height / 2.0f - 120));

        texts[1].setFont(font);
        texts[1].setCharacterSize(18);
        texts[1].setStyle(sf::Text::Bold);
    }

    void display(int duration)
    {
        w.create(sf::VideoMode(_width, _height), "Minesweeper");

        if (duration >= 0)
        {
            ranking _newrank[5];
            ranking _new(_username, duration);
            for (int i = 0; i < 5; i++)
            {
                if (_new.duration > _rank[i].duration)
                    _newrank[i] = _rank[i];
                else
                {
                    _newrank[i] = _new;
                    _new = _rank[i];
                }
            }
            for (int i = 0; i < 5; i++)
                _rank[i] = _newrank[i];
        }

        ofstream fout;
        fout.open(_path + "files/leaderboard.txt");
        for (int i = 0; i < 5; i++)
            fout << i_st(_rank[i].duration / 60) + ":" + i_st(_rank[i].duration % 60) + "," + _rank[i].name + "\n";
        fout.close();

        string disp;
        bool newrecord = false;
        for (int i = 0; i < 5; i++)
        {
            disp += to_string(i + 1) + ".\t" + i_st(_rank[i].duration / 60) + ":" + i_st(_rank[i].duration % 60) + "\t" + _rank[i].name;
            if (_rank[i].name == _username && _rank[i].duration == duration && !newrecord)
            {
                disp += "*";
                newrecord = true;
            }
            disp += "\n\n";
        }
        texts[1].setString(disp);
        texts[1].setPosition(centeringText(texts[1], _width / 2.0f, _height / 2.0f + 20));

        while (w.isOpen())
        {
            sf::Event e;
            while (w.pollEvent(e))
                listen(w, e);
            draw(w);
        }
    }

    string i_st(int i)
    {
        if (i > 9)
            return to_string(i);
        return "0" + to_string(i);
    }

    void listen(sf::RenderWindow &w, sf::Event &e)
    {
        if (e.type == sf::Event::Closed)
            w.close();
        else if (e.type == sf::Event::TextEntered)
        {
            sf::String input;
            input += e.text.unicode;
            if (input == "\e")
                w.close();
        }
    }
    void draw(sf::RenderWindow &w)
    {
        w.clear(_bgc);
        w.draw(texts[0]);
        w.draw(texts[1]);
        w.display();
    }
};