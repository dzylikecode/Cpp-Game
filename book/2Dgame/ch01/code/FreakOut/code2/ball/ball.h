#include "settings/global.h"
#include <SFML/Graphics.hpp>
#ifndef HUI_BALL_H
#define HUI_BALL_H
class Ball
{
public:
    sf::Vector2f velocity;
    sf::Color color;
    sf::CircleShape shape;
    float radius;
public:
    bool create(float x, float y, float radius, sf::Color color);
    void set_velocity(float vx, float vy);
    void update(void);
    void draw(sf::RenderWindow& window);
};
#endif