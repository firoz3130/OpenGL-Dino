#include<stdio.h>
#include<GL/glut.h>
typedef float point[3];
point v[] = { {0,0,1},{0,1,-1},{-1,-1,-1},{1,-1,-1} };
int n;

void triangle(point a, point b, point c)
{
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void divtri(point a, point b, point c, int m)
{
    point v1, v2, v3;
    int j;
    if (m > 0)
    {
        for (j = 0;j < 3;j++)
            v1[j] = (a[j] + b[j]) / 2;
        for (j = 0;j < 3;j++)
            v2[j] = (a[j] + c[j]) / 2;
        for (j = 0;j < 3;j++)
            v3[j] = (c[j] + b[j]) / 2;

        divtri(a, v1, v2, m - 1);
        divtri(c, v2, v3, m - 1);
        divtri(b, v3, v1, m - 1);
    }
    else
        triangle(a, b, c);
}


void tetra(int m)
{
    glColor3f(1, 0, 0);
    divtri(v[0], v[1], v[2], m);

    glColor3f(0, 1, 0);
    divtri(v[3], v[2], v[1], m);

    glColor3f(0, 0, 1);
    divtri(v[0], v[3], v[1], m);

    glColor3f(0, 0, 0);
    divtri(v[0], v[2], v[3], m);
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tetra(4);
    glFlush();
}

int main(int argc, char** argv)
{
    printf("enter the number of division ");
    scanf("%d", &n);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 840);
    glutCreateWindow("3D Gasket");
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);
    glutMainLoop();
}
