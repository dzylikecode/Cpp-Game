
// default screen size
#define SCREEN_WIDTH 640 // size of screen
#define SCREEN_HEIGHT 480

#define NUM_TEXTURES 10 // normally this would be a multiple of 16 or something!

int world_x = 0, // current position of viewing window
    world_y = 0;

// use an array of string pointers, could have used an
// array of chars or int, but harder to initialize
// the characters '0' - '9' represent bitmaps 0-9 in some texture memory
char *world[21] =
    {
        "111111111111111111111111111111",
        "100000000000000000000000000001",
        "100002222220000000000000077701",
        "100002222223333333333000077701",
        "100002222227777777773000070001",
        "100002222227777777773000070001",
        "100000000377777777773000070001",
        "107777700377777777773000070001",
        "177777770377777777773000770001",
        "107777700377777777773007700001",
        "100777770377777777773777000001",
        "100000707377777777773000000001",
        "100007777377777777773000000001",
        "100000000302222777773000000001",
        "100000000332222777773000000001",
        "100000000002222333333000000001",
        "100000666666666666666666600001",
        "100000800000000000000000800001",
        "100000800000000000000000800001",
        "100000000000000000000000000001",
        "111111111111111111111111111111",

};

// GAME PROGRAMMING CONSOLE FUNCTIONS ////////////////

int Game_Init(void *parms, int num_parms)
{
    // load in texture maps
    Load_Bitmap_File("SCROLLTEXTURES.BMP");

    // create the texture bob
    if (!Create_BOB(64, 64))
        return (0);

    // load each texture bitmap into the texture BOB object
    for (index = 0; index < NUM_TEXTURES; index++)
        Load_Frame_BOB(index % 4, index / 4);

    // set clipping rectangle to screen extents so mouse cursor
    // doens't mess up at edges
    RECT screen_rect = {0, 0, screen_width, screen_height - 32}; // 32 pixels at the bottom for controls
}

int Game_Main(void *parms, int num_parms)
{

    int index, index_x, index_y;  // looping vars
    int start_map_x, start_map_y, // map positions
        end_map_x, end_map_y;

    int offset_x, offset_y; // pixel offsets within cell

    // check for movement (scrolling)
    if (KEY_DOWN(VK_RIGHT))
    {
        if ((world_x += 4) >= 1280)
            world_x = 1279;
    }
    else if (KEY_DOWN(VK_LEFT))
    {
        if ((world_x -= 4) < 0)
            world_x = 0;
    }

    if (KEY_DOWN(VK_UP))
    {
        if ((world_y -= 4) < 0)
            world_y = 0;
    }
    else if (KEY_DOWN(VK_DOWN))
    {
        if ((world_y += 4) >= 896)
            world_y = 895;
    }

    // compute starting map indices by dividing position by size of cell
    start_map_x = world_x / 64; // use >> 6 for speed, but this is clearer
    start_map_y = world_y / 64;

    // compute end of map rectangle for best cast i.e. aligned on 64x64 boundary
    end_map_x = start_map_x + 10 - 1;
    end_map_y = start_map_y + 7 - 1;

    // now compute number of pixels in x,y we are within the tile, i.e
    // how much is scrolled off the edge?
    offset_x = -(world_x % 64);
    offset_y = -(world_y % 64);

    // adjust end_map_x,y for offsets
    if (offset_x)
        end_map_x++;

    if (offset_y)
        end_map_y++;

    // set starting position of first upper lh texture
    int texture_x = offset_x;
    int texture_y = offset_y;

    // draw the current window
    for (index_y = start_map_y; index_y <= end_map_y; index_y++)
    {
        for (index_x = start_map_x; index_x <= end_map_x; index_x++)
        {
            // set position to blit
            textures.x = texture_x;
            textures.y = texture_y;

            // set frame
            textures.curr_frame = world[index_y][index_x] - '0';

            // draw the texture
            Draw_BOB(&textures, lpddsback);

            // update texture position
            texture_x += 64;
        }

        // reset x postion, update y
        texture_x = offset_x;
        texture_y += 64;
    }

    // draw some info
    Draw_Text_GDI("USE ARROW KEYS TO MOVE, <ESC> to Exit.", 8, 8, RGB(255, 255, 255), lpddsback);

    sprintf(buffer, "World Position = [%d, %d]     ", world_x, world_y);
    Draw_Text_GDI(buffer, 8, screen_height - 32 - 24, RGB(0, 255, 0), lpddsback);
}