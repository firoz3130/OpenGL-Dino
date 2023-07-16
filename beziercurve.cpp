#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define p1 3.1416
typedef struct wcPt3D
{
    GLfloat x, y, z;
};
void bino(GLint n, GLint* c)
{
    GLint k, j;
    for (k = 0; k <= n; k++)
    {
        c[k] = 1;
        for (j = n; j >= k + 1; j--)
            c[k] *= j;
        for (j = n - k; j >= 2; j--)
            c[k] /= j;
    }
}
void computeBezPt(GLfloat u, wcPt3D* bezPt, GLint nctrlPts, wcPt3D* ctrlPts, GLint* c)
{
    GLint k, n = nctrlPts - 1;
    GLfloat bezBlendFunc;
    bezPt->x = bezPt->y = bezPt->z = 0.0;
    for (k = 0; k < nctrlPts; k++)
    {
        bezBlendFunc = c[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFunc;
        bezPt->y += ctrlPts[k].y * bezBlendFunc;
        bezPt->z += ctrlPts[k].z * bezBlendFunc;
    }
}
void bezier(wcPt3D* ctrlPts, GLint nctrlPts, GLint nBezcurvePts)
{
    wcPt3D bezcurvePt;
    GLfloat u;
    GLint* c, k;
    c = new GLint[nctrlPts];
    bino(nctrlPts - 1, c);
    glBegin(GL_LINE_STRIP);
    for (k = 0; k <= nBezcurvePts; k++)
    {
        u = GLfloat(k) / GLfloat(nBezcurvePts);
        computeBezPt(u, &bezcurvePt, nctrlPts, ctrlPts, c);
        glVertex2f(bezcurvePt.x, bezcurvePt.y);
    }
    glEnd();
    delete[]c;
}
void displayFunc()
{
    GLint nctrlPts = 4, nBezcurvePts = 20;
    static float theta = 0;
    wcPt3D ctrlPts[4] = { { 20, 100, 0 }, { 30, 110, 0 }, { 50, 90, 0 }, { 60, 100, 0 } };
    ctrlPts[1].x += 10 * sin(theta * p1 / 180.0);
    ctrlPts[1].y += 5 * sin(theta * p1 / 180.0);
    ctrlPts[2].x -= 10 * sin((theta + 30) * p1 / 180.0);
    ctrlPts[2].y -= 10 * sin((theta + 30) * p1 / 180.0);
    ctrlPts[3].x -= 4 * sin((theta)*p1 / 180.0);
    ctrlPts[3].y += sin((theta - 30) * p1 / 180.0);
    theta += 0.1;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    glPushMatrix();
    glLineWidth(5);
    glColor3f(255 / 255, 153 / 255.0, 51 / 255.0);
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlPts, nctrlPts, nBezcurvePts);
    }
    glColor3f(1, 1, 1);
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlPts, nctrlPts, nBezcurvePts);
    }
    glColor3f(19 / 255.0, 136 / 255.0, 8 / 255.0);
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(ctrlPts, nctrlPts, nBezcurvePts);
    }
    glPopMatrix();
    glColor3f(0.7, 0.5, 0.3);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(20, 100);
    glVertex2f(20, 40);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 130.0, 0.0, 130.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void fillMenu(int option)
{
    if (option == 1)
        glutDisplayFunc(displayFunc);
    if (option == 2)
        exit(0);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("BEZIER CURVE");
    glutCreateMenu(fillMenu);
    glutAddMenuEntry("Animate Flag", 1);
    glutAddMenuEntry("Stop", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(displayFunc);
    glutReshapeFunc(winReshapeFunc);
    glutMainLoop();
    return 0;
}