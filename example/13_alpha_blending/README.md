# alpha blending

## main

[Blend-Mode](https://wiki.libsdl.org/SDL_BlendMode)

1. get a texture
2. set blend mode

```cpp
//Set blending function
SDL_SetTextureBlendMode( mTexture, blending );
```

3. set alpha

```cpp
//Modulate texture alpha
SDL_SetTextureAlphaMod( mTexture, alpha );
```
