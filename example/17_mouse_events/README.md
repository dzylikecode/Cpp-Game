# mouse events

## main

`e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP`

`SDL_GetMouseState(&x, &y);`

通过消息发送, 传递给对方, 然后对方翻译为自身的状态

```cpp
//Set mouse over sprite
switch( e->type )
{
    case SDL_MOUSEMOTION:
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
    break;

    case SDL_MOUSEBUTTONDOWN:
    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
    break;

    case SDL_MOUSEBUTTONUP:
    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
    break;
}
```

## extensible

[mouse wheel](https://wiki.libsdl.org/SDL_MouseWheelEvent)
