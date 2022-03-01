# sound effects and music

## main

- init

```cpp
//Initialize SDL
if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
{
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
}

//Initialize SDL_mixer
if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
{
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
}

```

The first argument sets the sound frequency, and 44100 is a standard frequency that works on most systems. The second argument determines the sample format, which again here we're using the default. The third argument is the number of hardware channels, and here we're using 2 channels for stereo. The last argument is the sample size, which determines the size of the chunks we use when playing sound. 2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing sounds.

- Load sound effects

```cpp
//Load music
gMusic = Mix_LoadMUS( "21_sound_effects_and_music/beat.wav" );
if( gMusic == NULL )
{
    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
}
//Load sound effects
gScratch = Mix_LoadWAV( "21_sound_effects_and_music/scratch.wav" );
if( gScratch == NULL )
{
    printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
}
```

- playing

```cpp
switch( e.key.keysym.sym )
{
    //Play high sound effect
    case SDLK_1:
    Mix_PlayChannel( -1, gHigh, 0 );
    break;
    
    //Play medium sound effect
    case SDLK_2:
    Mix_PlayChannel( -1, gMedium, 0 );
    break;
    
    //Play low sound effect
    case SDLK_3:
    Mix_PlayChannel( -1, gLow, 0 );
    break;
    
    //Play scratch sound effect
    case SDLK_4:
    Mix_PlayChannel( -1, gScratch, 0 );
    break;
    
    case SDLK_9:
    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( gMusic, -1 );
    }
    //If music is being played
    else
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
    break;
    
    case SDLK_0:
    //Stop the music
    Mix_HaltMusic();
    break;
}
```

The first argument is the channel you want to use to play it. Since we don't care which channel it comes out of, we set the channel to negative 1 which will use the nearest available channel. The second argument is the sound effect and last argument is the number of times to repeat the effect. We only want it to play once per button press, so we have it repeat 0 times.

A channel in this case is not the same as a hardware channel that can represent the left and right channel of a stereo system. Every sound effect that's played has a channel associated with it. When you want to pause or stop an effect that is playing, you can halt its channel.

music:

last argument is the number of times to repeat it. Negative 1 is a special value saying we want to loop it until it is stopped.


If there is music playing, we check if the music is paused using Mix_PausedMusic. If the music is paused, we resume it using Mix_ResumeMusic. If the music is not paused we pause it using Mix_PauseMusic.

When 0 is pressed, we stop music if it's playing using Mix_HaltMusic.

- close

```cpp
//Free the sound effects
Mix_FreeChunk( gScratch );
Mix_FreeChunk( gHigh );
Mix_FreeChunk( gMedium );
Mix_FreeChunk( gLow );
gScratch = NULL;
gHigh = NULL;
gMedium = NULL;
gLow = NULL;

//Free the music
Mix_FreeMusic( gMusic );
gMusic = NULL;
```
