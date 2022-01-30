- [windows](#windows)
  - [target](#target)
  - [main](#main)
  - [NOTES](#notes)
    - [start](#start)
    - [close](#close)
    - [create window](#create-window)
      - [draw](#draw)

# windows

## target

getting a window to pop up

## main

## NOTES

It's important that we have the arguments of the function be an integer followed by a char\* array and the return type be an integer. Any other type of main function will cause an undefined reference to main. SDL requires this type of main so it is compatible with multiple platforms.

原因是, main 函数被重现定义, 如果不是这种类型, 则会导致未定义的引用 main, 在 Windows 上
main 函数被 SDL 重新定义了

### start

```cpp
if (SDL_Init(SDL_INIT_VIDEO) < 0)
{
    //When there's an error, SDL_Init returns -1.
    //When there's an error we want to print to the console what happened
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
}
```

### close

```cpp
// Quit SDL subsystems
SDL_Quit();
```

### create window

```cpp
//Create window
window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
if( window == NULL )
{
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
}
```

#### draw

1. get the window's surface so we can draw to it.

```cpp
//Get window surface
screenSurface = SDL_GetWindowSurface( window );
```

2. fill the surface with white

```cpp
//Fill the surface white
SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
```

**NOTES**: SDL_MapRGB is a function that takes the surface's format and the RGB values and returns the pixel value.

3. update the window

```cpp
//Update the surface
SDL_UpdateWindowSurface( window );
```

By default, most rendering systems out there are double buffered. These two buffers are the front and back buffer. When you draw something, it goes into the front buffer. When you update the window, the front buffer is copied to the back buffer. This is called double buffering.

4. close the window

```cpp
//Destroy window
SDL_DestroyWindow( window );
```
