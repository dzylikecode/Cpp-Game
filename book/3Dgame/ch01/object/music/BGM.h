#ifndef HUI_BGM_H
#define HUI_BGM_H
#include "SFML/Audio.hpp"

class BGM
{
private:
    sf::Music music;

public:
    void init();
};

extern BGM bgm;
#endif