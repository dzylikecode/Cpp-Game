
#include "paddle.h"
#include "ball.h"

bool check_collision(Paddle &paddle, Ball &ball)
{
    if (ball.position.x - ball.radius < paddle.position.x - paddle.shape.getSize().x / 2 ||
        ball.position.x + ball.radius > paddle.position.x + paddle.shape.getSize().x / 2)
    {
        return false;
    }
    if (ball.position.y - ball.radius < paddle.position.y - paddle.shape.getSize().y / 2 ||
        ball.position.y + ball.radius > paddle.position.y + paddle.shape.getSize().y / 2)
    {
        return false;
    }
    return true;
}