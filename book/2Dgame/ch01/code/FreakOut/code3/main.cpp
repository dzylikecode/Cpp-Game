// FREAKOUT.CPP - break game demo

#include <iostream>
#include "blackbox.h" // game library includes
#include <string>
#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <spdlog/spdlog.h>
// DEFINES

#define WINDOW_WIDTH 640 // size of window
#define WINDOW_HEIGHT 480

#define SCREEN_WIDTH WINDOW_WIDTH // size of screen
#define SCREEN_HEIGHT WINDOW_HEIGHT

// states for game loop
#define GAME_STATE_INIT 0
#define GAME_STATE_START_LEVEL 1
#define GAME_STATE_RUN 2
#define GAME_STATE_SHUTDOWN 3
#define GAME_STATE_EXIT 4

// block defines
#define NUM_BLOCK_ROWS 6
#define NUM_BLOCK_COLUMNS 8

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 16
#define BLOCK_ORIGIN_X 8
#define BLOCK_ORIGIN_Y 8
#define BLOCK_X_GAP 80
#define BLOCK_Y_GAP 32

// paddle defines
#define PADDLE_START_X (SCREEN_WIDTH / 2 - 16)
#define PADDLE_START_Y (SCREEN_HEIGHT - 32);
#define PADDLE_WIDTH 32
#define PADDLE_HEIGHT 8
#define PADDLE_COLOR 191

// ball defines
#define BALL_START_Y (SCREEN_HEIGHT / 2)
#define BALL_SIZE 4

// PROTOTYPES

// game console
int Game_Main(void *parms = NULL);

// GLOBALS

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Freak Out!");
sf::Font font;
inline void Draw_Rectangle(int x, int y, int w, int h, int color)
{
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(color, color, color));
    window.draw(rect);
}

inline void Draw_Text(int x, int y, std::string &text, int color)
{
    sf::Text txt(text, font, 12);
    txt.setPosition(x, y);
    txt.setFillColor(sf::Color(color, color, color));
    window.draw(txt);
}

int game_state = GAME_STATE_INIT; // starting state

int paddle_x = 0, paddle_y = 0; // tracks position of paddle
int ball_x = 0, ball_y = 0;     // tracks position of ball
int ball_dx = 0, ball_dy = 0;   // velocity of ball
int score = 0;                  // the score
int level = 1;                  // the current level
int blocks_hit = 0;             // tracks number of blocks hit

// this contains the game grid data

unsigned char blocks[NUM_BLOCK_ROWS][NUM_BLOCK_COLUMNS];

void Init_Blocks(void)
{
    // initialize the block field
    for (int row = 0; row < NUM_BLOCK_ROWS; row++)
        for (int col = 0; col < NUM_BLOCK_COLUMNS; col++)
            blocks[row][col] = row * 16 + col * 3 + 16;
}

void Draw_Blocks(void)
{
    // this function draws all the blocks in row major form
    int x1 = BLOCK_ORIGIN_X, // used to track current position
        y1 = BLOCK_ORIGIN_Y;

    // draw all the blocks
    for (int row = 0; row < NUM_BLOCK_ROWS; row++)
    {
        // reset column position
        x1 = BLOCK_ORIGIN_X;

        // draw this row of blocks
        for (int col = 0; col < NUM_BLOCK_COLUMNS; col++)
        {
            // draw next block (if there is one)
            if (blocks[row][col] != 0)
            {
                // draw block
                Draw_Rectangle(x1 - 4, y1 + 4,
                               BLOCK_WIDTH, BLOCK_HEIGHT, 0);

                Draw_Rectangle(x1, y1, BLOCK_WIDTH,
                               BLOCK_HEIGHT, blocks[row][col]);
            }

            // advance column position
            x1 += BLOCK_X_GAP;
        }

        // advance to next row position
        y1 += BLOCK_Y_GAP;
    }
}

void Process_Ball(void)
{
    // this function tests if the ball has hit a block or the paddle
    // if so, the ball is bounced and the block is removed from
    // the playfield note: very cheesy collision algorithm :)

    // first test for ball block collisions

    // the algorithm basically tests the ball against each
    // block's bounding box this is inefficient, but easy to
    // implement, later we'll see a better way

    int x1 = BLOCK_ORIGIN_X, // current rendering position
        y1 = BLOCK_ORIGIN_Y;

    int ball_cx = ball_x + (BALL_SIZE / 2), // computer center of ball
        ball_cy = ball_y + (BALL_SIZE / 2);

    // test of the ball has hit the paddle
    if (ball_y > (SCREEN_HEIGHT / 2) && ball_dy > 0)
    {
        // extract leading edge of ball
        int x = ball_x + (BALL_SIZE / 2);
        int y = ball_y + (BALL_SIZE / 2);

        // test for collision with paddle
        if ((x >= paddle_x && x <= paddle_x + PADDLE_WIDTH) &&
            (y >= paddle_y && y <= paddle_y + PADDLE_HEIGHT))
        {
            // reflect ball
            ball_dy = -ball_dy;

            // push ball out of paddle since it made contact
            ball_y += ball_dy;

            // add a little english to ball based on motion of paddle
            if (KEY_DOWN(Right))
                ball_dx -= (rand() % 3);
            else if (KEY_DOWN(Left))
                ball_dx += (rand() % 3);
            else
                ball_dx += (-1 + rand() % 3);

            // test if there are no blocks, if so send a message
            // to game loop to start another level
            if (blocks_hit >= (NUM_BLOCK_ROWS * NUM_BLOCK_COLUMNS))
            {
                game_state = GAME_STATE_START_LEVEL;
                level++;
            }

            // make a little noise
            MessageBeep(MB_OK);

            return;
        }
    }

    // now scan thru all the blocks and see of ball hit blocks
    for (int row = 0; row < NUM_BLOCK_ROWS; row++)
    {
        // reset column position
        x1 = BLOCK_ORIGIN_X;

        // scan this row of blocks
        for (int col = 0; col < NUM_BLOCK_COLUMNS; col++)
        {
            // if there is a block here then test it against ball
            if (blocks[row][col] != 0)
            {
                // test ball against bounding box of block
                if ((ball_cx > x1) && (ball_cx < x1 + BLOCK_WIDTH) &&
                    (ball_cy > y1) && (ball_cy < y1 + BLOCK_HEIGHT))
                {
                    // remove the block
                    blocks[row][col] = 0;

                    // increment global block counter, so we know
                    // when to start another level up
                    blocks_hit++;

                    // bounce the ball
                    ball_dy = -ball_dy;

                    // add a little english
                    ball_dx += (-1 + rand() % 3);

                    // make a little noise
                    MessageBeep(MB_OK);

                    // add some points
                    score += 5 * (level + (abs(ball_dx)));

                    // that's it -- no more block
                    return;
                }
            }

            // advance column position
            x1 += BLOCK_X_GAP;
        }

        // advance to next row position
        y1 += BLOCK_Y_GAP;
    }
}

int Game_Main(void *parms)
{
    char buffer[80]; // used to print text

    // what state is the game in?
    if (game_state == GAME_STATE_INIT)
    {
        window.setFramerateLimit(60);
        if (!font.loadFromFile("PlayfairDisplay-Regular.ttf"))
        {
            // error loading font
            spdlog::error("Error loading font");
            return 0;
        }
        // set the paddle position here to the middle bottom
        paddle_x = PADDLE_START_X;
        paddle_y = PADDLE_START_Y;

        // set ball position and velocity
        ball_x = 8 + rand() % (SCREEN_WIDTH - 16);
        ball_y = BALL_START_Y;
        ball_dx = -4 + rand() % (8 + 1);
        ball_dy = 6 + rand() % 2;

        // transition to start level state
        game_state = GAME_STATE_START_LEVEL;
    }

    else if (game_state == GAME_STATE_START_LEVEL)
    {
        // get a new level ready to run

        // initialize the blocks
        Init_Blocks();

        // reset block counter
        blocks_hit = 0;

        // transition to run state
        game_state = GAME_STATE_RUN;
    }

    else if (game_state == GAME_STATE_RUN)
    {

        // clear drawing surface for the next frame of animation
        Draw_Rectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 200);

        // move the paddle
        if (KEY_DOWN(Right))
        {
            // move paddle to right
            paddle_x += 8;

            // make sure paddle doesn't go off screen
            if (paddle_x > (SCREEN_WIDTH - PADDLE_WIDTH))
                paddle_x = SCREEN_WIDTH - PADDLE_WIDTH;
        }
        else if (KEY_DOWN(Left))
        {
            // move paddle to right
            paddle_x -= 8;

            // make sure paddle doesn't go off screen
            if (paddle_x < 0)
                paddle_x = 0;
        }

        // draw blocks
        Draw_Blocks();

        // move the ball
        ball_x += ball_dx;
        ball_y += ball_dy;

        // keep ball on screen, if the ball hits the edge of
        // screen then bounce it by reflecting its velocity
        if (ball_x > (SCREEN_WIDTH - BALL_SIZE) || ball_x < 0)
        {
            // reflect x-axis velocity
            ball_dx = -ball_dx;

            // update position
            ball_x += ball_dx;
        }

        // now y-axis
        if (ball_y < 0)
        {
            // reflect y-axis velocity
            ball_dy = -ball_dy;

            // update position
            ball_y += ball_dy;
        }
        else
            // penalize player for missing the ball
            if (ball_y > (SCREEN_HEIGHT - BALL_SIZE))
            {
                // reflect y-axis velocity
                ball_dy = -ball_dy;

                // update position
                ball_y += ball_dy;

                // minus the score
                score -= 100;
            }

        // next watch out for ball velocity getting out of hand
        if (ball_dx > 8)
            ball_dx = 8;
        else if (ball_dx < -8)
            ball_dx = -8;

        // test if ball hit any blocks or the paddle
        Process_Ball();

        // draw the paddle and shadow
        Draw_Rectangle(paddle_x - 8, paddle_y + 8,
                       PADDLE_WIDTH,
                       PADDLE_HEIGHT, 0);

        Draw_Rectangle(paddle_x, paddle_y,
                       PADDLE_WIDTH,
                       PADDLE_HEIGHT, PADDLE_COLOR);

        // draw the ball
        Draw_Rectangle(ball_x - 4, ball_y + 4, BALL_SIZE, BALL_SIZE, 255);
        Draw_Rectangle(ball_x, ball_y, BALL_SIZE,
                       BALL_SIZE, 0);

        // draw the info
        std::string str = boost::str(boost::format{"F R E A K O U T           Score %1%             Level %2%"} % score % level);
        Draw_Text(8, SCREEN_HEIGHT - 16, str, 56);

        window.display();

        // check of user is trying to exit
        if (KEY_DOWN(Escape))
        {
            // set exit state
            game_state = GAME_STATE_SHUTDOWN;
        }
    }

    else if (game_state == GAME_STATE_SHUTDOWN)
    {
        // switch to exit state
        game_state = GAME_STATE_EXIT;
    }

    return (1);
}

int main(int argc, char *argv[])
{
    while (window.isOpen())
    {
        // process all events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // update the game
        Game_Main(NULL);
    }

    return 0;
}