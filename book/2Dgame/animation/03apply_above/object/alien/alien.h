#ifndef HUI_ALIEN_H
#define HUI_ALIEN_H

#include "SFML/Graphics.hpp"
#include "boost/format.hpp"
#include "spdlog/spdlog.h"
#include "animate/AnimatedSprite.hpp"

class Background;

class Alien
{
    friend class Background;

public:
    enum Direction
    {
        E = 0,
        NE,
        N,
        NW,
        W,
        SW,
        S,
        SE,
        DIR_COUNT
    };

private:
    Animation animation[DIR_COUNT];
    AnimatedSprite sprite;
    Animation *currentAnimation;
    bool no_key_pressed;
    sf::Vector2f velocity;

public:
    void init();
    void input(sf::Event &event);
    void update(sf::Time &frame_time);
    void draw(sf::RenderWindow &window);

private:
    bool is_touch_floor();
};

extern Alien alien;
#endif