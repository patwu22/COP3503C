#include <fstream>
#include <iostream>
#include "welc.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[])
{
    unsigned int columns;
    unsigned int rows;
    unsigned int mines;
    string username;
    string path;
    if (argc == 1)
        path = "";
    else
        path = string(argv[1]);

    // Reading board_config.cfg
    ifstream fin;
    fin.open(path + "files/board_config.cfg");
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        columns = stoi(str);
        getline(fin, str);
        rows = stoi(str);
        getline(fin, str);
        mines = stoi(str);
        fin.close();
    }
    else
    {
        cout << "Can not open config file." << endl;
        return 0;
    }

    // Rendering window and font
    sf::RenderWindow w(sf::VideoMode(columns * 32, rows * 32 + 100), "Minesweeper");
    sf::Font font;
    if (!font.loadFromFile(path + "files/font.ttf"))
    {
        cout << "Can not load font from file." << endl;
        return 0;
    }

    // Windows
    window *currentWindow = new welc(columns, rows, font);

    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                w.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                sf::String input;
                input += event.text.unicode;

                // Escape key
                if (input == "\e")
                    w.close();
                // Enter key
                if (input == "\r" && currentWindow->index == 0)
                {
                    for (char c : currentWindow->_username)
                        username += tolower(c);
                    username[0] = toupper(username[0]);
                    if (username != "")
                    {
                        delete currentWindow;
                        currentWindow = new game(columns, rows, mines, path, username);
                    }
                }
            }
            currentWindow->listen(w, event);
        }
        w.clear(currentWindow->_bgc);
        currentWindow->draw(w);
        w.display();
    }

    delete currentWindow;
    return 0;
}
