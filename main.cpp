#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;
extern int map_wall[20][20];
extern int map_enemy[20][20];
extern int map_bullet[20][20];

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	gluOrtho2D(0,500,0,400);
}

void drawWall(int i, int j)
{
	glColor3f(1,0,0);
	glRectf(i*50, j*50, (i+1)*50, (j+1)*50);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (map_wall[i][j])
				drawWall(i, j);

	glutSwapBuffers();
}

void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
}
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("simple");
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}