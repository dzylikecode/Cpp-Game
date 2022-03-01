# viewport

## main

`SDL_RenderSetViewport( gRenderer, &topLeftViewport );`

topLeftViewport 会成为新的视口，作为 gRenderer 的全部视野

```cpp
//Render texture to screen
SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
```

这是针对 viewport 的
