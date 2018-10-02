#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "item.h"
#include <algorithm>
#include <list>

using namespace std;

// 문제...
// 1. 정적인 물체는 모두 map으로 관리...? (item, wall) 포함
// 2. enemy는 list로 관리??
// 3. 스무스한 움직임을 구현?
// 4. 몇초에 한번씩 enemy가 움직여야 하는지?

using namespace std;
Player player(10, 10);
list<Bullet> listBullet;
list<Enemy> listEnemy;
list<Item> listItem;
extern int map_wall[20][20];
extern int map_enemy[20][20];
extern int map_bullet[20][20];
extern int map_item[20][20];

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(player.x * 50 - 250,player.x * 50 + 250, player.y * 50 - 200, player.y * 50 + 200);
	glTranslatef(50, 0, 0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0, 0, 0.1, 0, 0, 0, 0, 1, 0);

}

void drawWall(int i, int j)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(i * 50, j * 50, 0);
	glColor3f(191/255.0,144/255.0,0/255.0);
	glRectf(0,0,50,50);
	glPopMatrix();
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (map_wall[i][j])
				drawWall(i, j);
	for (list<Bullet>::iterator it = listBullet.begin(); it != listBullet.end(); it++)
		(*it).draw();
	for (list<Item>::iterator it = listItem.begin(); it != listItem.end(); it++)
		(*it).draw();
	for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
		(*it).draw();
	player.draw();
	
	glutSwapBuffers();
}

void cameraMove()
{
	int left;
	int right;
	int bottom;
	int top;
	left = min(max(player.x * 50 - 250, 0), 500);
	right = left + 500;
	bottom = min(max(player.y * 50 - 200, 0), 600);
	top = bottom + 400;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glTranslatef(left, bottom, 0);
	gluOrtho2D(left, right, bottom, top);
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
	cameraMove();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		listBullet.push_back(Bullet(player.direction, player.x, player.y));
	}

	glutPostRedisplay();
}

void timer(int value)
{
	//those shall be merged into update func
	for (list<Bullet>::iterator it = listBullet.begin(); it != listBullet.end();)//bullet management
	{
		cout << "in bullet iterator";
		(*it).move();
		if ((*it).wallCollision())
		{
			(*it).~Bullet();
			listBullet.erase(it++);
		}
		else
			it++;
	}
	
	for (list<Item>::iterator it = listItem.begin(); it != listItem.end();)//item management
	{
		if ((*it).playerCollision())
		{
			(*it).~Item();
			listItem.erase(it++);
		}
		else
			it++;
	}

	for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end();)//enemy management
	{
		cout << "in enemy iterator";
		(*it).move();
		if ((*it).bulletCollision())
		{
			(*it).~Enemy();
			listEnemy.erase(it++);
		}
		else
			it++;
	}

	if (player.enemyCollision())
	{
		cout << "gameover" << endl;
	}

	glutPostRedisplay();
	glutTimerFunc(1, timer, 1);
}

void itemInit()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (map_item[i][j] != 0)
				listItem.push_back(Item(map_item[i][j], i, j));
}

void enemyInit()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (map_enemy[i][j] != 0)
				listEnemy.push_back(Enemy(i, j));
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutCreateWindow("simple");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 1);
	itemInit();
	enemyInit();
	glutMainLoop();
}