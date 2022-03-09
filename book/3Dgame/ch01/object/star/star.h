#ifndef HUI_STAR_H
#define HUI_STAR_H
#include "SFML/Graphics.hpp"

class Stars
{
public:
    static const int num_stars = 512;

private:
    class Star_item
    {
    public:
        sf::Vector3f position;
        sf::Vector3f velocity;
        sf::Color color;
    };

private:
    Star_item stars[num_stars];

public:
};
#endif