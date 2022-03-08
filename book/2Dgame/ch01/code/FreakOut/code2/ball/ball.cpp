#include "ball/ball.h"
#include "physic/physic.h"

bool Ball::create(float x, float y, float radius, sf::Color color)
{
    this->shape.setOrigin(radius, radius);
    this->shape.setPosition(x, y);
    this->shape.setRadius(radius);
    this->shape.setFillColor(color);
    this->radius = radius;
    this->color = color;
    return true;
}

void Ball::set_velocity(float vx, float vy)
{
    this->velocity.x = vx;
    this->velocity.y = vy;
}

void Ball::update(void)
{
    this->shape.move(this->velocity);
    auto rect = this->shape.getGlobalBounds();

    if (rect.left < 0)
    {
        this->velocity.x = -this->velocity.x;
        rect.left = 0;
    }
    else if (rect.left + rect.width > screen_width)
    {
        this->velocity.x = -this->velocity.x;
        rect.left = screen_width - rect.width;
    }
    if (rect.top < 0)
    {
        this->velocity.y = -this->velocity.y;
        rect.top = 0;
    }
    else if (rect.top + rect.height > screen_height)
    {
        this->velocity.y = -this->velocity.y;
        rect.top = screen_height - rect.height;
    }

    this->shape.setPosition(rect.left + this->radius,
                            rect.top + this->radius);
}

void Ball::draw(sf::RenderWindow &window)
{
    window.draw(this->shape);
}