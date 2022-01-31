- [event](#event)
  - [Game Loop](#game-loop)
  - [deal event](#deal-event)
  - [Next](#next)

# event


## Game Loop

we'll have the application loop while the user has not quit. This loop that keeps running while the application is active is called the main loop, which is sometimes called the game loop. It is the core of any game application.

```cpp

// While application is running
while (!quit) 
{
    // do something
}

```

## deal event

When you press a key, move the mouse, or touch a touch screen you put events onto the event queue.

The event queue will then store them in the order the events occured waiting for you to process them. 

![](https://lazyfoo.net/tutorials/SDL/03_event_driven_programming/enqueue.png)


```cpp
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
    //User requests quit
    if( e.type == SDL_QUIT )
    {
        quit = true;
    }
}
```

What this does is keep processing the event queue until it is empty.

What SDL_PollEvent does is take the most recent event from the event queue and puts the data from the event into the SDL_Event we passed into the function.

When the queue is empty, `SDL_PollEvent` will return 0. So what this piece of code does is keep polling events off the event queue until it's empty.

## Next

After we're done processing the events for our frame, we draw to the screen and update it