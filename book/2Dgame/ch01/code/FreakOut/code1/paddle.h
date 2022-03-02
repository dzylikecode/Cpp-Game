#include <SFML/Graphics.hpp>
#include "global.h"

class Paddle
{
public:
    sf::Vector2f position;
    sf::RectangleShape shape;

public:
    bool create(sf::Vector2f position)
    {
        this->position = position;
        shape.setSize(sf::Vector2f(100, 20));
        shape.setOrigin(shape.getSize() / 2.0f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
        return true;
    }
    void check_bound()
    {
        if (position.x - shape.getSize().x / 2 < 0)
        {
            position.x = shape.getSize().x / 2;
        }
        if (position.x + shape.getSize().x / 2 > screen_width)
        {
            position.x = screen_width - shape.getSize().x / 2;
        }
        if (position.y - shape.getSize().y / 2 < 0)
        {
            position.y = shape.getSize().y / 2;
        }
        if (position.y + shape.getSize().y / 2 > screen_height)
        {
            position.y = screen_height - shape.getSize().y / 2;
        }
    }
    void move_left()
    {
        position.x -= 15;
        check_bound();
        shape.setPosition(position);
    }
    void move_right()
    {
        position.x += 15;
        check_bound();
        shape.setPosition(position);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};