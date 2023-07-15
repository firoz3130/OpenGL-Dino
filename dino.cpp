#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <sstream>
#include <unistd.h>
static int animationPeriod = 4;
static int isAnimate = 0;
int score = 0;
const int fact = 3;
const int x = 80;
const double DEG2RAD = 3.1415926535897932384 / 180;
bool gameStarted = false;

static double w = 200;
static int flag = 0;
static int walk = 0;
static int x_ = 2500;
using namespace std;
bool isBend = false;
void welcomeScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color and position for the text
    glColor3f(0.0, 0.0, 0.0);
    GLfloat posX = 600;
    GLfloat posY = 1300;
    glRasterPos2f(posX, posY);

    // Display the welcome message
    std::string welcomeMessage = "Welcome to the DINO Game!\n";
    std::string welcomeMessage2 = "\n-->Press Space to start the game";
    std::string welcomeMessage3 = "\n-->Press Esc to exit the game";
    std::string welcomeMessage4 = "\n-->Press Up Arrow to jump";
    std::string welcomeMessage5 = "\nThis is the Dino Game Built using OpenGL and C++";
    std::string welcomeMessage6 = "\nBuilt By \nFiros K                1CD20CS046";
    std::string welcomeMessage7 = "\nR N Ravi              1CD20CS125";

    for (size_t i = 0; i < welcomeMessage.length(); i++)
    {
        if (welcomeMessage[i] == '\n')
        {
            posY -= 20; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else {
            glColor3f(1.0, 0.0, 1.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage[i]);
        }


    }
    for (size_t i = 0; i < welcomeMessage2.length(); i++)
    {
        if (welcomeMessage2[i] == '\n')
        {
            posY -= 40; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage2[i]);
    }
    for (size_t i = 0; i < welcomeMessage3.length(); i++)
    {
        if (welcomeMessage3[i] == '\n')
        {
            posY -= 60; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage3[i]);

    }
    for (size_t i = 0; i < welcomeMessage4.length(); i++)
    {
        if (welcomeMessage4[i] == '\n')
        {
            posY -= 80; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage4[i]);
    }
    for (size_t i = 0; i < welcomeMessage5.length(); i++)
    {
        if (welcomeMessage5[i] == '\n')
        {
            posY -= 100; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else
        {
            glColor3f(0.0, 1.0, 0.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage5[i]);
        }
    }
    for (size_t i = 0; i < welcomeMessage6.length(); i++)
    {
        if (welcomeMessage6[i] == '\n')
        {
            posY -= 120; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else
        {
            glColor3f(1.0, 0.0, 0.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage6[i]);
        }
    }
    for (size_t i = 0; i < welcomeMessage7.length(); i++)
    {
        if (welcomeMessage7[i] == '\n')
        {
            posY -= 140; // Move the position down by 20 units
            glRasterPos2f(posX, posY);
        }
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, welcomeMessage7[i]);
        }
    }
    glFlush();
}




void animate(int value)
{
    if (isAnimate)
    {
        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // 27 is the ascii value of esc key,terminates the program if esc key is pressed
        exit(0);
    case ' ': // the space character
        if (!gameStarted)
        {
            gameStarted = true;
            glutPostRedisplay();
        }
        else
        {
            if (isAnimate)
                isAnimate = 0;
            else
            {
                isAnimate = 1;
                animate(1);
            }
        }
        break;
    }
}

bool collision(double len)
{
    if (abs(157 + x - (x_ + x + 50)) <= 100 + x)
    { // both if has to be satisfied in order to collide
        if (5 * fact + w <= 650 * len)
            return 1; // indicating a collision has occurred
        return 0;
    }
    // returns false, indicating no collision.
    return 0;
}
// callback function for special key input (such as arrow keys) in the GLUT library.
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_UP && flag == 0 && w <= 200.0)
    {             // if the input key is the "Up" arrow key (GLUT_KEY_UP), and if the flag variable is equal to 0,
        flag = 1; // sets the value of flag to 1, indicating that  character movement in the main display function
    }

    glutPostRedisplay(); // notify GLUT that the display should be updated, which will trigger the main display function.
}
void draw_circle(double theta, double inner_radius, double outer_radius, int x, int y, int sin_sign = 1, int cos_sign = 1)
{
    glBegin(GL_POINTS);
    glColor3f(0.0, 1.0, 0.0);
    // glColor3f(0.0/ 255.0, 0.0/ 255.0, 0.0/ 255.0);
    for (double r = outer_radius; r >= inner_radius; r -= 3.0)
    {
        for (double i = 0; i < theta; i++)
        {
            double degInRad = i * DEG2RAD;
            glVertex2f(cos_sign * cos(degInRad) * r + x, sin_sign * sin(degInRad) * r + y);
        }
    }
    glEnd();
}

void generate_tree(int x_, double len)
{

    int x = 30;
    glColor3f(0.0, 1.0, 0.0);
    // glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
    glBegin(GL_POLYGON);
    glVertex2f(x_, 250 * len);
    glVertex2f(x_ + x, 250 * len);
    glVertex2f(x_ + x, 650 * len);
    glVertex2f(x_, 650 * len);
    glEnd();

    draw_circle(280.0, 0.0, x / 2, x_ + x / 2, 650 * len);

    glBegin(GL_POLYGON);
    glVertex2f(x_ + x + 25, 400 * len);
    glVertex2f(x_ + x + 50, 400 * len);
    glVertex2f(x_ + x + 50, 600 * len);
    glVertex2f(x_ + x + 25, 600 * len);
    glEnd();

    draw_circle(180.0, 0.0, 25.0 / 2, x_ + x + 75.0 / 2, 600 * len);

    glBegin(GL_POLYGON);
    glVertex2f(x_ - 25, 400 * len);
    glVertex2f(x_ - 50, 400 * len);
    glVertex2f(x_ - 50, 600 * len);
    glVertex2f(x_ - 25, 600 * len);
    glEnd();

    draw_circle(180.0, 0.0, 25.0 / 2, x_ - 75.0 / 2, 600 * len);
    draw_circle(100.0, 25, 50, x_ + x, 400 * len, -1);
    draw_circle(90.0, 25, 50, x_, 400 * len, -1, -1);
}

void reset()
{
    w = 200;
    flag = 0;
    walk = 0;
    x_ = 2500;
    animationPeriod = 4;
    isAnimate = 0;
}
// code for drawing the dinosaur is located in the render() function
void render(void)
{
    if (!gameStarted)
    {
        welcomeScreen();
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2);
    glBegin(GL_POINTS);
    // grass color
    glColor3f(0.0, 1.0, 0.0);
    //   glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
    for (int i = 0; i < 100; i++)
    {
        glVertex2f(rand() % 2000, 200);
        glVertex2f(rand() % 2000, 180);
        glVertex2f(rand() % 2000, 170);
        glVertex2f(rand() % 2000, 160);
        glVertex2f((rand() + 31) % 2000, 150);
        glVertex2f((rand() + 13) % 2000, 140);
        glVertex2f((rand() + 13) % 2000, 130);
        glVertex2f((rand() + 17) % 2000, 120);
        glVertex2f((rand() + 23) % 2000, 110);
        glVertex2f((rand() + 17) % 2000, 100);
        glVertex2f((rand() + 23) % 2000, 90);
        glVertex2f((rand() + 17) % 2000, 80);
    }
    glEnd(); // marks end of point drawing section
    int y = 0;

    generate_tree(x_, 1.0);
    generate_tree(x_ + 100, 0.95);
    //speed of the entire game is controlled by the animationPeriod variable
    //below x_ is the x coordinate of the dinosaur also speed of the dinosaur is controlled by the animationPeriod variable
    if (x_ >= 0)
        x_ -= 5;
    else
    {
        x_ = 2000 + rand() % 400;
    }
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f((1) / 255.0, (1) / 255.0, (1) / 255.0); // The glColor3f function sets the current color for drawing, which in this case is black (0, 0, 0).
    glVertex2f(0, 250);
    glVertex2f(2000, 250);
    glEnd();

    glLineWidth(10);
    glBegin(GL_LINES);
    // change the color of dino
    glColor3f(0.0, 0.0, 0.0);
    // glColor3f(0 / 255.0, 0 / 255.0, 0 / 255.0);
    glVertex2f(10 + x, 75 * fact + w);
    glVertex2f(10 + x, 45 * fact + w);
    glVertex2f(15 + x, 65 * fact + w);
    glVertex2f(15 + x, 40 * fact + w);
    glVertex2f(20 + x, 60 * fact + w);
    glVertex2f(20 + x, 35 * fact + w);
    glVertex2f(25 + x, 55 * fact + w);
    glVertex2f(25 + x, 35 * fact + w);
    glVertex2f(30 + x, 55 * fact + w);
    glVertex2f(30 + x, 35 * fact + w);
    glVertex2f(35 + x, 55 * fact + w);
    glVertex2f(35 + x, 25 * fact + w);
    glVertex2f(40 + x, 60 * fact + w);
    glVertex2f(40 + x, 5 * fact + w - walk);
    glVertex2f(45 + x, 65 * fact + w);
    glVertex2f(45 + x, 15 * fact + w);
    glVertex2f(45 + x, 10 * fact + w - walk);
    glVertex2f(45 + x, 5 * fact + w - walk);
    glVertex2f(50 + x, 10 * fact + w - walk);
    glVertex2f(50 + x, 5 * fact + w - walk);
    glVertex2f(55 + x, 10 * fact + w - walk);
    glVertex2f(55 + x, 5 * fact + w - walk);
    glVertex2f(50 + x, 65 * fact + w);
    glVertex2f(50 + x, 20 * fact + w);
    glVertex2f(55 + x, 70 * fact + w);
    glVertex2f(55 + x, 25 * fact + w);
    glVertex2f(63 + x, 75 * fact + w);
    glVertex2f(63 + x, 20 * fact + w);
    glVertex2f(70 + x, 115 * fact + w);
    glVertex2f(70 + x, 5 * fact + w + walk);
    glVertex2f(78 + x, 120 * fact + w);
    glVertex2f(78 + x, 25 * fact + w);
    glVertex2f(78 + x, 10 * fact + w + walk);
    glVertex2f(78 + x, 5 * fact + w + walk);
    glVertex2f(85 + x, 10 * fact + w + walk);
    glVertex2f(85 + x, 5 * fact + w + walk);
    glVertex2f(87 + x, 120 * fact + w);
    glVertex2f(87 + x, 115 * fact + w);
    glVertex2f(87 + x, 110 * fact + w);
    glVertex2f(87 + x, 30 * fact + w);
    glVertex2f(95 + x, 120 * fact + w);
    glVertex2f(95 + x, 35 * fact + w);
    glVertex2f(103 + x, 120 * fact + w);
    glVertex2f(103 + x, 75 * fact + w);
    glVertex2f(103 + x, 65 * fact + w);
    glVertex2f(103 + x, 60 * fact + w);
    glVertex2f(110 + x, 65 * fact + w);
    glVertex2f(110 + x, 60 * fact + w);
    glVertex2f(118 + x, 65 * fact + w);
    glVertex2f(118 + x, 55 * fact + w);
    glVertex2f(112 + x, 120 * fact + w);
    glVertex2f(112 + x, 85 * fact + w);
    glVertex2f(112 + x, 80 * fact + w);
    glVertex2f(112 + x, 75 * fact + w);
    glVertex2f(120 + x, 120 * fact + w);
    glVertex2f(120 + x, 85 * fact + w);
    glVertex2f(120 + x, 80 * fact + w);
    glVertex2f(120 + x, 75 * fact + w);
    glVertex2f(126 + x, 120 * fact + w);
    glVertex2f(126 + x, 85 * fact + w);
    glVertex2f(126 + x, 80 * fact + w);
    glVertex2f(126 + x, 75 * fact + w);
    glVertex2f(135 + x, 120 * fact + w);
    glVertex2f(135 + x, 85 * fact + w);
    glVertex2f(135 + x, 80 * fact + w);
    glVertex2f(135 + x, 75 * fact + w);
    glVertex2f(142 + x, 120 * fact + w);
    glVertex2f(142 + x, 85 * fact + w);
    glVertex2f(150 + x, 120 * fact + w);
    glVertex2f(150 + x, 85 * fact + w);
    glVertex2f(157 + x, 115 * fact + w);
    glVertex2f(157 + x, 85 * fact + w);

    glEnd();

    if (collision(1.0))
    {
        sleep(1); // small delay given if collision occurs so that score can be seen
        reset();
        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(700, 710);

        std::stringstream ss;
        // increase the size of font size

        ss << " " << score;
        // use a string stream for displaying the score
        std::string scoreStr = ss.str();
        std::string gameover = "Game Over! Your Score is: ";
        // display gameover string only once
        for (size_t i = 0; i < gameover.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameover[i]);
        }
        for (size_t i = 0; i < scoreStr.length(); i++)
        {

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreStr[i]);
        }
        // till here the code is to show the score
        glFlush();
        score = -1;
    }
    if (!collision(1.0))
    {
        score++;
    }
    if (w <= 200)
    {
        if (walk == -20)
            walk = 20;
        else
        {
            walk = -20;
        }
    }
    else
    {
        walk = 0;
    }

    if (flag == 1)
    {
        if (w <= 1000)
        {
            w = w + 8;
        }
        else
        {
            flag = 0;
        }
    }
    else if (w >= 200)
        w = w - 8;
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(900, 10);
    std::stringstream ss;
    ss << "Score: " << score;
    // use a string stream for displaying the score
    std::string scoreStr = ss.str();
    for (size_t i = 0; i < scoreStr.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreStr[i]);
    }
    // till here the code is to show the score
    glFlush();
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION); // This line sets the current matrix mode to GL_PROJECTION.
    // The matrix mode determines which matrix stack is the target for subsequent matrix ops.
    gluOrtho2D(0.0, 2000, 0.0, 2000); // sets up an orthogonal projection for 2D rendering
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(1230, 650);
    glutInitWindowPosition(50, 0);
    glutCreateWindow("Dinosaur!!");
    setup();
    glutDisplayFunc(render);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();
}