# Color Keying

## main

we color key the image with SDL_SetColorKey before creating a texture from it. 

`SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );`