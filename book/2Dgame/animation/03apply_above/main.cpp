#include "SFML/Graphics.hpp"
#include "animate/AnimatedSprite.hpp"
#include "spdlog/spdlog.h"
#include "object/alien/alien.h"
#include "object/background/background.h"
#include "object/global/global.h"


void init_main();


sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Animations!");

int main(int argc, char *argv[])
{
    init_main();
    sf::Clock frameClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            alien.input(event);
        }
        sf::Time frameTime = frameClock.restart();
        alien.update(frameTime);
        background.update();
        window.clear(sf::Color::White);
        background.draw(window);
        alien.draw(window);
        window.display();
    }
    return 0;
}

void init_main()
{
    alien.init();
    background.init();
}