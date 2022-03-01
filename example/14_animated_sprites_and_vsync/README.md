# animated sprites and vsync

## main

```cpp
//Create vsynced renderer for window
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
if( gRenderer == NULL )
{
    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    success = false;
}
```

VSync allows the rendering to update at the same time as when your monitor updates during vertical refresh.

it seems that the vsync is not working on WSL.

```cpp
//Render current frame
SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
```

可以在一张图片里面存放多个动作, 通过改变图片的 clip 来实现动作.
