# color modulation

## main

```cpp
//Modulate texture
SDL_SetTextureColorMod( mTexture, red, green, blue );
```

just like scale:

srcC = srcC \* (color / 255)

You may have noticed that SDL_SetTextureColorMod accepts Uint8 as arguments for the color components. An Uint8 is just an integer that is Unsigned and 8bit. This means it goes from 0 to 255. 128 is about halfway between 0 and 255, so when you modulate green to 128 it halves the green component for any pixel on the texture.
