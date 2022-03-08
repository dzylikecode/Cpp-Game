#include "object/background/background.h"
#include "object/alien/alien.h"
#include "object/global/global.h"

// floor color for RGB color collision scan
#define FLOOR_COLOR_R 41
#define FLOOR_COLOR_G 231
#define FLOOR_COLOR_B 41

void Background::init()
{
    static sf::Texture texture[3];
    landscape_image[0].loadFromFile("res/background/landscape1_24.bmp");
    landscape_image[1].loadFromFile("res/background/landscape2_24.bmp");
    landscape_image[2].loadFromFile("res/background/landscape3_24.bmp");
    texture[0].loadFromImage(landscape_image[0]);
    landscape_sprite[0].setTexture(texture[0]);
    texture[1].loadFromImage(landscape_image[1]);
    landscape_sprite[1].setTexture(texture[1]);
    texture[2].loadFromImage(landscape_image[2]);
    landscape_sprite[2].setTexture(texture[2]);
    current_landscape = 0;
}

void Background::update()
{
    auto alien_rect = alien.sprite.getGlobalBounds();
    auto alien_x = alien_rect.left + alien_rect.width / 2;
    auto alien_y = alien_rect.top;
    if (alien_x > screen_width)
    {
        if (current_landscape < 2)
        {
            current_landscape++;
            alien.sprite.setPosition(- alien_rect.width / 2, alien_y);
        }
        else
        {
            current_landscape = 2;
            alien.sprite.setPosition(screen_width - alien_rect.width / 2, alien_y);
        }
    }
    else if (alien_x < 0)
    {
        if (current_landscape > 0)
        {
            current_landscape--;
            alien.sprite.setPosition(screen_width - alien_rect.width / 2, alien_y);
        }
        else
        {
            current_landscape = 0;
            alien.sprite.setPosition(- alien_rect.width / 2, alien_y);
        }
    }
}

void Background::draw(sf::RenderWindow &window)
{
    window.draw(landscape_sprite[current_landscape]);
}

bool Background::is_floor(int x, int y)
{
    sf::Color color = landscape_image[current_landscape].getPixel(x, y);
    if (color.r == FLOOR_COLOR_R && color.g == FLOOR_COLOR_G && color.b == FLOOR_COLOR_B)
    {
        return true;
    }
    return false;
}

Background background;