#ifndef HUI_SOUND_H
#define HUI_SOUND_H
#include <SFML/Audio.hpp>

class Sound_lib
{
private:
    sf::SoundBuffer explosion_buffer;
    sf::SoundBuffer laser_buffer;
    sf::Sound explosion_sound;
    sf::Sound laser_sound;

public:
    void init();
    void play_explosion();
    void play_laser();
};

extern Sound_lib sound_lib;
#endif