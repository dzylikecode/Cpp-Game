#include "object/cross/cross.h"

void Cross::input(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left)
        {
            velocity.x = -speed;
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            velocity.x = speed;
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
            velocity.y = -speed;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            velocity.y = speed;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
        {
            velocity.x = 0;
        }
        else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
        {
            velocity.y = 0;
        }
    }
}