/*************************************************************************
/   breakout.c
/
/   Computer Science 50
/   Problem Set 3 - Darren Green - 11/29/2015
/
*************************************************************************/

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

//  brick dimensions
#define BHEIGHT 10
#define BWIDTH 34

//  brick top row starting level
#define BSTART 40

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//  paddle size
#define PHEIGHT 10
#define PWIDTH 50

//  paddle position
#define PLEVEL 550

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
                    
    //  ball velocity
    double x_velocity = (drand48() * 2.5);
    double y_velocity = 2.5;
    
    //  initial object locations
    double paddle_start_x = getX(paddle);
    double paddle_start_y = getY(paddle);
    double ball_start_x = getX(ball);
    double ball_start_y = getY(ball);

    //  click to begin playing
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // Control paddle movement
            GEvent movement = getNextEvent(MOUSE_EVENT);
            
            if (movement != NULL)
            {
                if (getEventType(movement) == MOUSE_MOVED)
                {
                    double x = getX(movement) - (PWIDTH / 2);
                    double y = PLEVEL;
                    setLocation(paddle, x, y);
                }
            }
        
        //  Control ball movement
            
            //  ball movement
            move(ball, x_velocity, y_velocity);
            
            //  x-axis ball confinement
            if ((getX(ball) + getWidth(ball) >= WIDTH) || (getX(ball) <= 0))
            {
                x_velocity = -x_velocity; 
            }                                 
            
            //  y-axis ball confinement
            
            //  if ball hits top of screen, bounce
            if (getY(ball) + getHeight(ball) <= 0)
            {
                y_velocity = -y_velocity;
            }
            
            pause(10);
            
        //  if ball hits bottom of screen
            if (getY(ball) + getHeight(ball) >= HEIGHT)
            {                                                
                //  lose one life
                lives--;
                
                //  check if any lives left: if not, exit
                if (lives == 0)
                {
                    break;
                }
                
                //  reset ball position and resume play on click
                setLocation(ball, ball_start_x, ball_start_y);
                setLocation(paddle, paddle_start_x, paddle_start_y);
                waitForClick();
            }
            
        //  handle collisions between objects
        
            //  ball and paddle
            GObject object = detectCollision(window, ball);
            
            if (object != NULL)
            {
                if (object == paddle)
                {
                    //  The ball bounces off the paddle
                    y_velocity = -y_velocity;                
                }
                
                //  When a ball hits a brick: remove brick and bounce
                if ((strcmp(getType(object), "GRect") == 0) && (object != paddle))
                {                
                    removeGWindow(window, object);
                    y_velocity = -y_velocity;
                    points++;
                    updateScoreboard(window, label, points);
                }
            }
            
        //  winning the game
        if (points == 50)
        {
            setLabel(label, "YOU WIN!");            
            break;
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

//  Initializes window with a grid of bricks.
void initBricks(GWindow window)
{      
    //  Draw the bricks: rows and then columns, L to R
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            //  declare vars for brick parameters
            double bstartx = (5 + ((BWIDTH + 5) * i));
            double bstarty = (BSTART + ((BHEIGHT + 5) * j));
            
            //  draw the actual bricks
            GRect brick = newGRect(bstartx, bstarty, BWIDTH, BHEIGHT);
            setFilled(brick, true);
          
            //  change color based on row
            switch (j)
            {
                case 0:
                    setColor(brick, "RED");
                    break;
                case 1:
                    setColor(brick, "ORANGE");
                    break;
                case 2:
                    setColor(brick, "YELLOW");
                    break;
                case 3:
                    setColor(brick, "GREEN");
                    break;
                case 4:
                    setColor(brick, "CYAN");
                    break; 
            }
            
            //  post the brick to the screen
            add(window, brick);
        }
    }
}

//  Instantiates ball in center of window.  Returns ball.
GOval initBall(GWindow window)
{   
    //  declare vars for ball start location based
    double ball_startx = (WIDTH / 2);
    double ball_starty = (HEIGHT / 2);
    
    //  declare vars for ball dimensions based on #define criteria
    double ball_height = RADIUS;
    double ball_width = RADIUS;
    
    //  draw the ball in the middle of the window
    GOval ball = newGOval(ball_startx, ball_starty, ball_height, ball_width);
    setFilled(ball, true);
    setColor(ball, "DARK_GRAY");
    add(window, ball);
    
    //  return ball per problem spec
    return ball;
}

//  Instantiates paddle in bottom-middle of window.
GRect initPaddle(GWindow window)
{
    //  declare vars for paddle start location based on GWindow specs in #define
    double pstartx = ((WIDTH / 2) - (PWIDTH / 2));
    double pstarty = PLEVEL;
    
    //  declare vars for paddle height and width based on #define criteria
    double paddle_width = PWIDTH;
    double paddle_height = PHEIGHT;
    
    //  draw the paddle in the window
    GRect paddle = newGRect(pstartx, pstarty, paddle_width, paddle_height);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    
    return paddle;
}

//  Instantiates, configures, and returns label for scoreboard.
GLabel initScoreboard(GWindow window)
{   
    //  declare the label and config parameters
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif-50");
    setColor(score, "LIGHT_GRAY");
    
    //  set label to correct location on the screen    
    int x = WIDTH / 2 - 10;
    int y = HEIGHT / 2 - 40;
    setLocation(score, x, y);
    
    //  draw the label
    add(window, score);
    
    return score;
}

//  Updates scoreboard's label, keeping it centered in window.
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/****************************************************************
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 ****************************************************************/
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
