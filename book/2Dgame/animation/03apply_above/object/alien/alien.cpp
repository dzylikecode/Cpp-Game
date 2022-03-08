#include "object/alien/alien.h"
#include "object/background/background.h"

void Alien::init()
{
    const int alien_width = 72;
    const int alien_height = 74;
#define SPRITE_POS_X(col) (col * (alien_width + 1) + 1)
#define SPRITE_POS_Y(row) (row * (alien_height + 1) + 1)
    sf::IntRect frame[4];
    frame[0] = sf::IntRect(SPRITE_POS_X(0), SPRITE_POS_Y(0), alien_width, alien_height);
    frame[1] = sf::IntRect(SPRITE_POS_X(1), SPRITE_POS_Y(0), alien_width, alien_height);
    frame[2] = sf::IntRect(SPRITE_POS_X(2), SPRITE_POS_Y(0), alien_width, alien_height);
    frame[3] = sf::IntRect(SPRITE_POS_X(0), SPRITE_POS_Y(1), alien_width, alien_height);
    static sf::Texture texture[DIR_COUNT]; // here we can use static
    for (int i = 0; i < 8; i++)
    {
        sf::Image temp_img;
        if (!temp_img.loadFromFile(boost::str(boost::format("res/alien/Quensp%d_24.bmp") % i)))
        {
            spdlog::error("Failed to load alien spritesheet!");
            return;
        }
        temp_img.createMaskFromColor(temp_img.getPixel(5, 5));
        // temp_img.createMaskFromColor(temp_img.getPixel(0, 0));
        texture[i].loadFromImage(temp_img);
        animation[i].setSpriteSheet(texture[i]);
        animation[i].addFrame(frame[0]);
        animation[i].addFrame(frame[1]);
        animation[i].addFrame(frame[0]);
        animation[i].addFrame(frame[2]);
    }

    currentAnimation = &animation[E];
    sprite.pause();
    sprite.setLooped(true);
    no_key_pressed = true;
    sprite.setPosition(100.0f, 100.0f);
}

void Alien::input(sf::Event &event)
{
    velocity = sf::Vector2f(0, 0);
    no_key_pressed = true;
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            currentAnimation = &animation[W];
            no_key_pressed = false;
            velocity.x -= 60; // 如果有多次按键，则会有多个移动
            break;
        case sf::Keyboard::Right:
            currentAnimation = &animation[E];
            no_key_pressed = false;
            velocity.x += 60;
            break;
        default:
            break;
        }
    }
}

void Alien::update(sf::Time &frame_time)
{
    sprite.play(*currentAnimation);
    sprite.move(velocity * frame_time.asSeconds());
    sprite.move(0, 2); // move down, because of gravity
    while (is_touch_floor())
    {
        sprite.move(0, -1); // move up, because of floor
    }

    if (no_key_pressed)
    {
        sprite.stop();
    }
    sprite.update(frame_time);
}

void Alien::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

bool Alien::is_touch_floor()
{
    auto pos_rect = sprite.getGlobalBounds();
    auto x_start = pos_rect.left + 16;
    auto x_end = pos_rect.left + pos_rect.width - 32;
    auto y_start = pos_rect.top + 24;
    auto y_end = pos_rect.top + pos_rect.height - 12;
    for (int i = x_start; i < x_end; i++)
    {
        for (int j = y_start; j < y_end; j++)
        {
            if (background.is_floor(i, j))
            {
                return true;
            }
        }
    }
    return false;
}


Alien alien;