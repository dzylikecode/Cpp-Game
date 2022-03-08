#include <SFML/Graphics.hpp>
#include "settings/global.h"
#include "config/config.h"

enum GAME_STATE
{
    GAME_STATE_START,
    GAME_STATE_RUNNING,
    GAME_STATE_PAUSED,
    GAME_STATE_OVER
};
using namespace sf;

bool bPause = false;
bool bExit = false;

void game_main(RenderWindow &window);
int main(int argc, char *argv[])
{

    RenderWindow window(VideoMode(screen_width, screen_height), "Freak Out!");
    window.setFramerateLimit(90);
    GAME_STATE state = GAME_STATE_START;
    if (!init_game())
    {
        goto label_init_game_failed;
    }

    while (window.isOpen())
    {
        switch (state)
        {
        case GAME_STATE_START:
            state = GAME_STATE_RUNNING;
            break;
        case GAME_STATE_RUNNING:
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                bPause = !bPause;
            }
            if (bPause)
            {
                state = GAME_STATE_PAUSED;
            }
            game_main(window);
            break;
        case GAME_STATE_PAUSED:
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                bPause = !bPause;
            }
            if (!bPause)
            {
                state = GAME_STATE_RUNNING;
            }
            break;
        case GAME_STATE_OVER:
            goto label_main_end;
            break;
        }
    }
label_main_end:
    return 0;
label_init_game_failed:
    spdlog::error("init_game() failed");
    return 1;
}

void game_main(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }
    window.clear();
    ball.update();
    ball.draw(window);
    window.display();
}