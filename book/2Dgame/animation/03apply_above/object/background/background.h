#ifndef HUI_BACKGROUND_H
#define HUI_BACKGROUND_H

#include "SFML/Graphics.hpp"
class Background
{
public:
private:
    sf::Image landscape_image[3];
    sf::Sprite landscape_sprite[3];
    int current_landscape;
public:
    void init();
    void update();
    void draw(sf::RenderWindow& window);
    bool is_floor(int x, int y);
};

extern Background background;

#endif