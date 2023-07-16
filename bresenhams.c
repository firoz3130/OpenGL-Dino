#include<GL/glut.h>
#include<stdio.h>
int x1 = 120, x2 = 180, y1 = 80, y2 = 180;

void drawpixel(int x, int y)
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void brenhamslinedraw(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1, dy = y2 - y1;
    int p = 2 * dy - dx;
    int twody = 2 * dy;
    int twodyminusdx = 2 * (dy - dx);
    int x = x1, y = y1;
    if (dx < 0)
    {
        x = x2;
        y = y2;
        x2 = x1;
    }
    drawpixel(x, y);
    while (x < x2)
    {
        x++;
        if (p < 0)
            p += twody;
        else
        {
            y++;
            p += twodyminusdx;
        }
        drawpixel(x, y);
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    brenhamslinedraw(x1, y1, x2, y2);
    glFlush();
}

int main(int argc, char** argv)
{
    // printf("enter start point x1 and x2:");
     //scanf("%d%d", &x1, &y1);
     //printf("enter end point y1 and y2:");
     //scanf("%d%d", &x2, &y2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
