# geometry rendering

## main

- clean
  
```cpp
//Clear screen
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
SDL_RenderClear( gRenderer );
```

- draw solid rectangle
```cpp
//Render red filled quad
SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
SDL_RenderFillRect( gRenderer, &fillRect );
```
know that the member variables that make up an SDL rect are x, y, w, and h for the x position, y position, width, and height respectively.

- draw outline rectangle
  
```cpp
//Render green outlined quad
SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );		
SDL_RenderDrawRect( gRenderer, &outlineRect );
```

- draw line

```cpp
//Draw blue horizontal line
SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );		
SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
```

- draw dot

```cpp
//Draw vertical line of yellow dots
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
{
    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
}
```

## show

```cpp
//Update screen
SDL_RenderPresent( gRenderer );
```

## coordinate system

y axis is upside down

 Making the y coordinate larger makes it go down and making the y coordinate smaller makes it go up.