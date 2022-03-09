#include "object/music/BGM.h"

void BGM::init()
{
    music.openFromFile("res/music/midifile2.ogg");
    music.setLoop(true);
    music.play();
}

BGM bgm;