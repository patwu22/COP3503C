#pragma once
#include "window.h"

class welc : public window
{
    unsigned int _width;
    unsigned int _height;
    sf::Text texts[3];

public:
    welc(unsigned int columns, unsigned int rows, sf::Font &font)
    {
        index = 0;
        _width = columns * 32.0f;
        _height = rows * 32.0f + 100;

        texts[0].setString("WELCOME TO MINESWEEPER!");
        texts[0].setFont(font);
        texts[0].setCharacterSize(24);
        texts[0].setStyle(sf::Text::Underlined | sf::Text::Bold);
        texts[0].setPosition(centeringText(texts[0], _width / 2.0f, _height / 2.0f - 150));

        texts[1].setString("Enter your name:");
        texts[1].setFont(font);
        texts[1].setCharacterSize(20);
        texts[1].setStyle(sf::Text::Bold);
        texts[1].setPosition(centeringText(texts[1], _width / 2.0f, _height / 2.0f - 75));

        texts[2].setString("|");
        texts[2].setFont(font);
        texts[2].setCharacterSize(18);
        texts[2].setFillColor(sf::Color::Yellow);
        texts[2].setStyle(sf::Text::Bold);
        texts[2].setPosition(centeringText(texts[2], _width / 2.0f, _height / 2.0f - 45));
    }

    void listen(sf::RenderWindow &w, sf::Event &e)
    {
        if (e.type == sf::Event::TextEntered)
        {
            sf::String input;
            input += e.text.unicode;
            if (input == "\b" && _username != "")
                _username = _username.substr(0, _username.size() - 1);
            if (_username.size() < 10 && isalpha(input.toAnsiString()[0]))
                _username += input.toAnsiString()[0];
            texts[2].setString(_username + "|");
            texts[2].setPosition(centeringText(texts[2], _width / 2.0f, _height / 2.0f - 45));
        }
    }

    void draw(sf::RenderWindow &w)
    {
        for (const sf::Text &t : texts)
            w.draw(t);
    }
};
