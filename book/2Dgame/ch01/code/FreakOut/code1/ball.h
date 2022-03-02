#include <SFML/Graphics.hpp>
#include "global.h"

class Ball
{
private:
    sf::Vector2f velocity;
    sf::Color color;

public:
    float radius;
    sf::CircleShape shape;
    sf::Vector2f position;

private:
    void check_bound()
    {
        if (position.x - radius < 0)
        {
            position.x = radius;
            velocity.x = -velocity.x;
        }
        if (position.x + radius > screen_width)
        {
            position.x = screen_width - radius;
            velocity.x = -velocity.x;
        }
        if (position.y - radius < 0)
        {
            position.y = radius;
            velocity.y = -velocity.y;
        }
        if (position.y + radius > screen_height)
        {
            position.y = screen_height - radius;
            velocity.y = -velocity.y;
        }
    }

public:
    bool create(sf::Vector2f position, float radius, sf::Color color = sf::Color::Red)
    {
        this->position = position;
        this->radius = radius;
        this->color = color;
        this->velocity = sf::Vector2f(4, 4);
        shape.setPosition(position);
        shape.setRadius(radius);
        shape.setFillColor(color);
        return true;
    }
    void move()
    {
        position += velocity;
        check_bound();
        shape.setPosition(position);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};
