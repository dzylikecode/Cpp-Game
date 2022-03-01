# timing

## main

```cpp

startTime = SDL_GetTicks();

//Set text to be rendered
timeText.str( "" );
timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime; 

```