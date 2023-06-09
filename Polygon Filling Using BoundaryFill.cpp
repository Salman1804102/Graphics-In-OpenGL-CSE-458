#include<windows.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

float fillColor[3] = {0.0, 1.0, 0.0};
float borderColor[3] = {0.0, 0.0, 1.0};
int xi, yi;
int z1 = 800, z2 = 800;

void polygon(int x1, int y1, int x2, int y2)
{
    glColor3fv(borderColor);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void display()
{
    glClearColor(0.6, 0.5, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT);
    polygon(100, 250, 200, 350);
    glFlush();
}

void pp(int x, int y, float f[3])
{
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}


void gp(int x, int y, float pixels[3])
{
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

void boundaryFill(int x, int y, float fillColor[3], float borderColor[3])
{
    float interiorColor[3];
    gp(x, y, interiorColor);
    if((interiorColor[0] != borderColor[0]) && (interiorColor[1] != borderColor[1]) && (interiorColor[2] != borderColor[2]) &&
            (interiorColor[0] != fillColor[0]) && (interiorColor[1] != fillColor[1]) && (interiorColor[2] != fillColor[2]))
    {
        pp(x, y, fillColor);
        boundaryFill(x+1, y, fillColor, borderColor);
        boundaryFill(x-1, y, fillColor, borderColor);
        boundaryFill(x, y+1, fillColor, borderColor);
        boundaryFill(x, y-1, fillColor, borderColor);
    }
}

void mouse(int btn, int state, int x, int y)
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xi = x;
        yi= z2 - y;
        boundaryFill(xi, yi, fillColor, borderColor);
    }
}


void myinit()
{
    glViewport(0,0,z1,z2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)z1,0.0,(GLdouble)z2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(z1,z2);
    glutCreateWindow("Boundary Fill");
    glutDisplayFunc(display);
    myinit();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
