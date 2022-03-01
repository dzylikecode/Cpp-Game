# key states

## main

```cpp
//Set texture based on current keystate
const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
if( currentKeyStates[ SDL_SCANCODE_UP ] )
```
