- [Image](#image)
  - [target](#target)
  - [suggestions](#suggestions)
  - [surface](#surface)
  - [show image](#show-image)
  - [NOTES](#notes)

# Image

## target

put an image on the window

## suggestions

only cover key parts of source code

## surface

An SDL surface is just an image data type that contains the pixels of an image
along with all data needed to render it. SDL surfaces use software rendering
which means it uses the CPU to render. It is possible to render hardware images
but it's a bit more difficult so we're going to learn it the easy way first.
In future tutorials we'll cover how to render GPU accelerated images.

Notice that these are pointers to SDL surfaces.

The reason is that

1. we'll be dynamically allocating memory to load images
2. it's better to reference an image by memory location.
   > Imagine you had a game with a brick wall that consisted of the same brick image being rendered multiple times (like Super Mario Bros). It's wasteful to have dozens of copies of the image in memory when you can have one copy of the image and render it over and over again.

to show images inside of the window so we need to get the image inside of the
window. So we call SDL_GetWindowSurface to grab the surface contained by the window.

## show image

1. load image

loads an image from a file and returns a pointer to the surface.

```cpp
// Load splash image
gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
```

2. blt image

```cpp
// Apply the image
SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
```

What blitting does is take a source surface and stamps a copy of it onto the destination surface. The first argument of SDL_BlitSurface is the source image.

3. update window

When you make draw calls like SDL_BlitSurface, you render to the back buffer. What you see on the screen is the front buffer. The reason we do this is because most frames require drawing multiple objects to the screen. If we only had a front buffer, we would be able to see the frame as things are being drawn to it which means we would see unfinished frames. So what we do is draw everything to the back buffer first and once we're done we swap the back and front buffer so now the user can see the finished frame.

This also means that you don't call SDL_UpdateWindowSurface after every blit,
only after all the blits for the current frame are done.

4. free surface

```cpp
//Deallocate surface
SDL_FreeSurface( gHelloWorld );
gHelloWorld = NULL;
```

We do this by freeing it with `SDL_FreeSurface`.
Don't worry about the screen surface, `SDL_DestroyWindow` will take care of it.

## NOTES

应该关心资源的释放:

1. surface 的释放 (window 的 surface 不需要释放)
2. window 的关闭
