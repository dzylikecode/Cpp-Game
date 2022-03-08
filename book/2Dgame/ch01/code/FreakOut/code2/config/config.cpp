#include "config/config.h"
#include "ball/ball.h"

Ball ball;

bool init_game()
{
    // - ball:
    if (!ball.create(screen_width / 2, screen_height / 2, 5, sf::Color::Red))
        return false;
    ball.set_velocity(3, 3);
    return true;
}