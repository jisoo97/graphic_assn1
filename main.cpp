#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "player.h"
using namespace std;
extern int map[20][20];
Player player(10, 10);
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
			if (map_wall[i][j] == 1)
				drawWall(i, j);
	player.draw();
	glutSwapBuffers();
}

void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		player.move(player.x, player.y+1);
		break;
	case GLUT_KEY_DOWN:
		player.move(player.x, player.y - 1);
		break;
	case GLUT_KEY_LEFT:
		player.move(player.x-1, player.y);
		break;
	case GLUT_KEY_RIGHT:
		player.move(player.x+1, player.y);
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutCreateWindow("simple");
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
}