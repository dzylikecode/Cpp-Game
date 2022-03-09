#include "object/sound/sound.h"
#include "spdlog/spdlog.h"

void Sound_lib::init()
{
    if (!explosion_buffer.loadFromFile("sound/explosion.wav"))
    {
        spdlog::error("Failed to load explosion.wav");
    }
    if (!laser_buffer.loadFromFile("sound/laser.wav"))
    {
        spdlog::error("Failed to load laser.wav");
    }
    explosion_sound.setBuffer(explosion_buffer);
    laser_sound.setBuffer(laser_buffer);
}

void Sound_lib::play_explosion()
{
    explosion_sound.play();
}

void Sound_lib::play_laser()
{
    laser_sound.play();
}

Sound_lib sound_lib;