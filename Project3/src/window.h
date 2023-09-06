#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class window
{
protected:
    sf::Vector2f centeringText(sf::Text &t, float x, float y)
    {
        return sf::Vector2f(x - t.getGlobalBounds().width / 2.0f, y - t.getGlobalBounds().height / 2.0f);
    }

public:
    int index;
    string _username;
    sf::Color _bgc = sf::Color::Blue;

    virtual void listen(sf::RenderWindow &w, sf::Event &e) = 0;
    virtual void draw(sf::RenderWindow &w) = 0;

    virtual ~window() {}
};
