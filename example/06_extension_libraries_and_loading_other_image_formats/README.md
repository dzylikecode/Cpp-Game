# load multiple image types

## main

1. initialize SDL_Image
   > ```cpp
   > //Initialize PNG loading
   > int imgFlags = IMG_INIT_PNG;
   > if( !( IMG_Init( imgFlags ) & imgFlags ) )
   > {
   >   printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
   > 	success = false;
   > }
   > ```
   >
   > If the flags that are returned do not contain the flags we requested, that means there's an error.
2. close SDL_Image

```cpp
//Quit SDL subsystems
IMG_Quit();
SDL_Quit();
```

## load image

```cpp
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else
            {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }

    return success;
}
```
