#include "SFML/Graphics.hpp"
#include "object/global/global.h"
#include "object/music/BGM.h"
int main()
{
    bgm.init();
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}