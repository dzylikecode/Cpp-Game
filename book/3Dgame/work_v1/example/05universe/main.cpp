#include "SFML/Graphics.hpp"
#include "object/settings/hui_setting.h"
#include "object/static/hui_static.h"
#include "object/player/hui_player.h"
int main()
{
    using namespace hui::triD;
    hui_player player;
    hui_static static_obj(player.camera);
    sf::RenderWindow window(video_mode, "SFML works!");
    window.setFramerateLimit(60);
    sf::Clock clock;
    player.init();
    static_obj.init();

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            player.input(event);
        }
        auto delta_time = clock.restart();
        auto fps = 1.f / delta_time.asSeconds();
        static_obj.update();
        player.update(delta_time);
        window.clear(Color::Black);
        window.draw(static_obj);
        window.draw(player);
        window.display();
        std::cout << "FPS: " << fps << "\r";
    }
    return 0;
}