#pragma once
#include "window.h"
#include "core.h"
#include "board.h"
#include <chrono>

class game : public window
{
    unsigned int _columns;
    unsigned int _rows;
    unsigned int _num_mines;
    unsigned int _state;
    unsigned int _pause;
    bool _debug;
    sf::Texture texs[20];
    sf::Sprite *backg = nullptr;
    sf::Sprite *tiles = nullptr;
    sf::Sprite *mines = nullptr;
    sf::Sprite *flags = nullptr;
    sf::Sprite face;
    sf::Sprite debug;
    sf::Sprite pause;
    sf::Sprite leader;
    sf::Sprite counter[4];
    sf::Sprite timer[4];
    chrono::steady_clock clock;
    chrono::time_point<chrono::steady_clock> start;
    int duration;
    core *_core = nullptr;
    board *_board = nullptr;

public:
    game(unsigned int columns, unsigned int rows, unsigned int num_mines, string path, string username)
    {
        index = 1;
        _columns = columns;
        _rows = rows;
        _num_mines = num_mines;
        _username = username;
        _bgc = sf::Color::White;

        // Load images
        texs[0].loadFromFile(path + "files/images/debug.png");
        texs[1].loadFromFile(path + "files/images/digits.png");
        texs[2].loadFromFile(path + "files/images/face_happy.png");
        texs[3].loadFromFile(path + "files/images/face_lose.png");
        texs[4].loadFromFile(path + "files/images/face_win.png");
        texs[5].loadFromFile(path + "files/images/flag.png");
        texs[6].loadFromFile(path + "files/images/leaderboard.png");
        texs[7].loadFromFile(path + "files/images/mine.png");
        texs[8].loadFromFile(path + "files/images/number_1.png");
        texs[9].loadFromFile(path + "files/images/number_2.png");
        texs[10].loadFromFile(path + "files/images/number_3.png");
        texs[11].loadFromFile(path + "files/images/number_4.png");
        texs[12].loadFromFile(path + "files/images/number_5.png");
        texs[13].loadFromFile(path + "files/images/number_6.png");
        texs[14].loadFromFile(path + "files/images/number_7.png");
        texs[15].loadFromFile(path + "files/images/number_8.png");
        texs[16].loadFromFile(path + "files/images/pause.png");
        texs[17].loadFromFile(path + "files/images/play.png");
        texs[18].loadFromFile(path + "files/images/tile_hidden.png");
        texs[19].loadFromFile(path + "files/images/tile_revealed.png");

        // Core
        _core = new core(_columns, _rows, _num_mines);
        _board = new board(_columns, _rows, path, _username);

        // Background
        backg = new sf::Sprite[_columns * _rows];
        for (int i = 0; i < _columns * _rows; i++)
        {
            backg[i].setTexture(texs[19]);
            backg[i].setPosition((i % _columns) * 32, (i / _columns) * 32);
        }

        // Tiles
        tiles = new sf::Sprite[_columns * _rows];
        for (int i = 0; i < _columns * _rows; i++)
            tiles[i].setPosition((i % _columns) * 32, (i / _columns) * 32);

        // Flags
        flags = new sf::Sprite[_columns * _rows];
        for (int i = 0; i < _columns * _rows; i++)
        {
            flags[i].setTexture(texs[5]);
            flags[i].setPosition((i % _columns) * 32, (i / _columns) * 32);
        }

        // Others
        face.setPosition(_columns * 16 - 32, (_rows + 0.5f) * 32);
        debug.setTexture(texs[0]);
        debug.setPosition(_columns * 32 - 304, (_rows + 0.5f) * 32);
        pause.setPosition(_columns * 32 - 240, (_rows + 0.5f) * 32);
        leader.setTexture(texs[6]);
        leader.setPosition(_columns * 32 - 176, (_rows + 0.5f) * 32);
        for (int i = 0; i < 4; i++)
        {
            counter[i].setTexture(texs[1]);
            counter[i].setPosition(12 + 21 * i, (_rows + 0.5f) * 32 + 16);
        }
        counter[0].setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
        for (int i = 0; i < 2; i++)
        {
            timer[i].setTexture(texs[1]);
            timer[i].setPosition(_columns * 32 - 97 + 21 * i, (_rows + 0.5f) * 32 + 16);
        }
        for (int i = 2; i < 4; i++)
        {
            timer[i].setTexture(texs[1]);
            timer[i].setPosition(_columns * 32 - 54 + 21 * (i - 2), (_rows + 0.5f) * 32 + 16);
        }

        reset();
    }

    void reset()
    {
        for (int i = 0; i < _columns * _rows; i++)
        {
            _core->tiles[i] = 0;
            _core->flags[i] = false;
        }
        _core->setMines();
        delete[] mines;
        mines = new sf::Sprite[_num_mines];
        int count = 0;
        for (int i = 0; i < _columns * _rows; i++)
        {
            if (_core->mines[i])
            {
                mines[count].setPosition((i % _columns) * 32, (i / _columns) * 32);
                count++;
            }
        }
        _state = 0;
        _pause = 0;
        _debug = false;
        start = clock.now();
        duration = 0;
    }

    void listen(sf::RenderWindow &w, sf::Event &e)
    {
        if (e.type == sf::Event::MouseButtonReleased)
        {
            int x = e.mouseButton.x / 32;
            int y = e.mouseButton.y / 32;
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (_pause == 0 && x < _columns && y < _rows && _state == 0)
                {
                    _state = _core->onclick_left(x, y);
                    if (_state != 0)
                        duration += (int)chrono::duration_cast<chrono::seconds>(clock.now() - start).count();
                    if (_state == 2)
                    {
                        w.clear(_bgc);
                        draw(w);
                        w.display();
                        _board->display(duration);
                        sf::Event event;
                        while (w.pollEvent(event))
                        {
                        }
                    }
                }
                else if (e.mouseButton.x > _columns * 16 - 32 && e.mouseButton.x < _columns * 16 + 32 && e.mouseButton.y > (_rows + 0.5f) * 32 && e.mouseButton.y < (_rows + 2.5f) * 32)
                    reset();
                else if (_state == 0 && _pause == 0 && e.mouseButton.x > _columns * 32 - 304 && e.mouseButton.x < _columns * 32 - 240 && e.mouseButton.y > (_rows + 0.5f) * 32 && e.mouseButton.y < (_rows + 2.5f) * 32)
                {
                    if (_debug)
                        _debug = false;
                    else
                        _debug = true;
                }
                else if (_state == 0 && e.mouseButton.x > _columns * 32 - 240 && e.mouseButton.x < _columns * 32 - 176 && e.mouseButton.y > (_rows + 0.5f) * 32 && e.mouseButton.y < (_rows + 2.5f) * 32)
                {
                    if (_pause == 0)
                    {
                        _pause = 1;
                        duration += (int)chrono::duration_cast<chrono::seconds>(clock.now() - start).count();
                    }
                    else
                    {
                        _pause = 0;
                        start = clock.now();
                    }
                }
                else if (e.mouseButton.x > _columns * 32 - 176 && e.mouseButton.x < _columns * 32 - 112 && e.mouseButton.y > (_rows + 0.5f) * 32 && e.mouseButton.y < (_rows + 2.5f) * 32)
                {
                    if (_state == 0 && _pause == 0)
                        duration += (int)chrono::duration_cast<chrono::seconds>(clock.now() - start).count();
                    bool _pause_tmp = false;
                    if (_pause == 1)
                        _pause_tmp = true;
                    _pause = 1;
                    w.clear(_bgc);
                    draw(w);
                    w.display();
                    _board->display(-1);
                    sf::Event event;
                    while (w.pollEvent(event))
                    {
                    }
                    if (!_pause_tmp)
                        _pause = 0;
                    start = clock.now();
                }
            }
            else if (_state == 0 && _pause == 0 && e.mouseButton.button == sf::Mouse::Right)
            {
                if (x < _columns && y < _rows)
                    _core->onclick_right(x, y);
            }
        }
    }

    void draw(sf::RenderWindow &w)
    {
        // Background
        for (int i = 0; i < _columns * _rows; i++)
            w.draw(backg[i]);
        // Flags Counter
        int flag_c = _num_mines;
        for (int i = 0; i < _columns * _rows; i++)
        {
            if (_core->flags[i])
                flag_c--;
        }
        if (_state == 2)
            flag_c = 0;
        // Game
        if (_pause == 0)
        {
            for (int i = 0; i < _columns * _rows; i++)
            {
                tiles[i].setTexture(texs[18 + _core->tiles[i]]);
                w.draw(tiles[i]);
            }
            for (int i = 0; i < _columns * _rows; i++)
            {
                if (_core->flags[i])
                    w.draw(flags[i]);
            }
            if (_debug || _state != 0)
            {
                for (int i = 0; i < _num_mines; i++)
                {
                    if (_state == 2)
                        mines[i].setTexture(texs[5]);
                    else
                        mines[i].setTexture(texs[7]);
                    w.draw(mines[i]);
                }
            }
            face.setTexture(texs[2 + _state]);
        }
        // Others
        w.draw(face);
        w.draw(debug);
        pause.setTexture(texs[16 + _pause]);
        w.draw(pause);
        w.draw(leader);

        if (flag_c < 0)
        {
            w.draw(counter[0]);
            flag_c = -flag_c;
        }
        counter[1].setTextureRect(sf::IntRect(flag_c / 100 % 10 * 21, 0, 21, 32));
        counter[2].setTextureRect(sf::IntRect(flag_c / 10 % 10 * 21, 0, 21, 32));
        counter[3].setTextureRect(sf::IntRect(flag_c % 10 * 21, 0, 21, 32));
        w.draw(counter[1]);
        w.draw(counter[2]);
        w.draw(counter[3]);

        int d = 0;
        if (_state == 0 && _pause == 0)
            d = (int)chrono::duration_cast<chrono::seconds>(clock.now() - start).count();
        timer[0].setTextureRect(sf::IntRect((d + duration) / 600 % 10 * 21, 0, 21, 32));
        timer[1].setTextureRect(sf::IntRect((d + duration) / 60 % 10 * 21, 0, 21, 32));
        timer[2].setTextureRect(sf::IntRect((d + duration) % 60 / 10 * 21, 0, 21, 32));
        timer[3].setTextureRect(sf::IntRect((d + duration) % 60 % 10 * 21, 0, 21, 32));
        w.draw(timer[0]);
        w.draw(timer[1]);
        w.draw(timer[2]);
        w.draw(timer[3]);
    }

    ~game()
    {
        delete[] backg;
        backg = nullptr;
        delete[] tiles;
        tiles = nullptr;
        delete[] mines;
        mines = nullptr;
        delete[] flags;
        flags = nullptr;
        delete _core;
        _core = nullptr;
        delete _board;
        _board = nullptr;
    }
};
