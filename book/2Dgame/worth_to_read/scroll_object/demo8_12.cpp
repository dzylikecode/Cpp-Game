
#define SCREEN_WIDTH 640 // size of screen
#define SCREEN_HEIGHT 480

// size of universe, could be anything
#define MAX_UNIVERSE_X 6400
#define MAX_UNIVERSE_Y 4800

#define NUM_OBJECTS_UNIVERSE 256 // number of objects in the universe

// used to flag type of object
#define GENERATOR_OBJ 0
#define BEACON_OBJ 1
#define ALIEN_OBJ 2

// need something to hold each object
typedef struct SPARSE_OBJ_TYP
{
    int type; // type of object: beacon, generator, or alien
              // could have just used a bob_ptr here, but I like
              // doing this the hard way so you can exactly what's happening

    int x, y; // position of object

} SPARSE_OBJ, *SPARSE_OBJ_PTR;

// demo globals
BOB generator, // the generator BOB
    alien,     // a little alien ship BOB
    beacon;    // a beacon BOB

int world_x = 0, // current position of viewing window
    world_y = 0;

SPARSE_OBJ world[NUM_OBJECTS_UNIVERSE]; // our world consists of 256 objects randomly placed in the universe
                                        // that is 10x10

int Game_Init(void *parms, int num_parms)
{

    // load in the generator bob image
    Load_Bitmap_File("GENS4.BMP");

    // create the generator bob
    if (!Create_BOB(72, 84))
        return (0);

    // load each bitmap into the generator BOB object
    for (index = 0; index < 4; index++)
        Load_Frame_BOB(index % 4, index / 4);

    // set up stating state of bob
    Set_Animation_BOB(&generator, 0);
    Set_Anim_Speed_BOB(&generator, 4);

    // load in the alien bob image
    Load_Bitmap_File("ALIENS0.BMP");

    // create the alien bob
    if (!Create_BOB(56, 30))
        return (0);

    // load each bitmap into the alien BOB object
    for (index = 0; index < 8; index++)
        Load_Frame_BOB(index % 5, index / 5);

    // set up stating state of bob
    Set_Animation_BOB(&alien, 0);
    Set_Anim_Speed_BOB(&alien, 4);

    // load in the beacon bob image
    Load_Bitmap_File("PIPE0.BMP");

    // create the alien bob
    if (!Create_BOB(42, 36, 8))
        return (0);

    // load each bitmap into the beacon BOB object
    for (index = 0; index < 8; index++)
        Load_Frame_BOB(index % 6, index / 6);

    // set up stating state of bob
    Set_Animation_BOB(&beacon, 0);
    Set_Anim_Speed_BOB(&beacon, 4);

    // now generate the sparse universe
    for (index = 0; index < NUM_OBJECTS_UNIVERSE; index++)
    {
        // set random position
        world[index].x = rand() % MAX_UNIVERSE_X;
        world[index].y = rand() % MAX_UNIVERSE_Y;

        // set type
        world[index].type = rand() % 3; // 0, 1, 2 generator, alien, beacon
    }
}

int Game_Main(void *parms, int num_parms)
{
    // this is the workhorse of your game it will be called
    // continuously in real-time this is like main() in C
    // all the calls for you game go here!

    int index, index_x, index_y; // looping vars
    int screen_x, screen_y;      // screen coords
    int width, height, type;     // used to extract bob info
    int x0, y0, x1, y1;          // used to compute the upper left and lower right corners of each object
    int visible = 0;             // number of visible objects

    BOB_PTR object_ptr; // the object that is going to be rendered

    // check for movement (scrolling)
    if (KEY_DOWN(VK_RIGHT))
    {
        if ((world_x += 8) >= 5760)
            world_x = 5760 - 1;
    }
    else if (KEY_DOWN(VK_LEFT))
    {
        if ((world_x -= 8) < 0)
            world_x = 0;
    }

    if (KEY_DOWN(VK_UP))
    {
        if ((world_y -= 8) < 0)
            world_y = 0;
    }
    else if (KEY_DOWN(VK_DOWN))
    {
        if ((world_y += 8) >= 4320)
            world_y = 4320 - 1;
    }

    // based on current world position which defines the viewport, i.e,
    // world_x, world_y to world_x+640-1, world_y+480-1, scan the object list
    // determine any object in that region translate it to screen coords and render it

    for (index = 0, visible = 0; index < NUM_OBJECTS_UNIVERSE; index++)
    {
        // get the object position
        x0 = world[index].x;
        y0 = world[index].y;

        // now translate to screen coords, could have done above, but clearer
        x0 = x0 - world_x;
        y0 = y0 - world_y;

        // get type, so we can compute size
        type = world[index].type;

        // compute size
        switch (type)
        {
        case GENERATOR_OBJ:
        {
            // get size of this object
            width = generator.width;
            height = generator.height;

            // point to it to render it easier without another switch
            object_ptr = &generator;
        }
        break;

        case BEACON_OBJ:
        {
            // get size of this object
            width = beacon.width;
            height = beacon.height;

            // point to it to render it easier without another switch
            object_ptr = &beacon;
        }
        break;

        case ALIEN_OBJ:
        {
            // get size of this object
            width = alien.width;
            height = alien.height;

            // point to it to render it easier without another switch
            object_ptr = &alien;
        }
        break;

        default:
            break;
        }

        // compute extents based on width,height
        x1 = x0 + width - 1;
        y1 = y0 + height - 1;

        // do clip trivial clip
        if ((x0 >= SCREEN_WIDTH) || (x1 < 0) || (y0 >= SCREEN_HEIGHT) || (y1 < 0))
            continue; // don't need to render this one
        else
        {
            // render this object
            object_ptr->x = x0;
            object_ptr->y = y0;

            Draw_BOB(object_ptr, lpddsback);

            visible++;
        }
    }

    // animate all the bobs
    Animate_BOB(&generator);
    Animate_BOB(&beacon);
    Animate_BOB(&alien);

    // draw some info
    Draw_Text_GDI("USE ARROW KEYS TO MOVE, <ESC> to Exit.", 8, 8, RGB(0, 255, 0), lpddsback);

    sprintf(buffer, "World Position = [%d, %d]  Objects Visible = %d, Objects Clipped = %d   ", world_x, world_y, visible, 256 - visible);
    Draw_Text_GDI(buffer, 8, screen_height - 32, RGB(0, 255, 0), lpddsback);
}
