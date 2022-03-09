#ifndef HUI_CROSS_H
#define HUI_CROSS_H

#include "SFML/Graphics.hpp"

class Cross
{
private:
    const int speed = 8;

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    public:
    void input(const sf::Event& event);
};

#endif