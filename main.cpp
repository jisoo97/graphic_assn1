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

//To do list
/*
1. enemy 다 잡으면 game over
2. item legend

3. map 바꾸기
4. item 시간 제한?
*/
Player player(10, 10);
list<Bullet> listBullet;
list<Enemy> listEnemy;
list<Item> listItem;
extern int map_wall[20][20];
extern int map_enemy[20][20];
extern int map_bullet[20][20];
extern int map_item[20][20];
int enemy_move = 0;
int bullet_speed = 4;

void reshape(int w, int h)
{
	
	glViewport(0,0, w, h);
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
	glColor3f(86 / 255.0, 52 / 255.0, 27 / 255.0);
	glRectf(0,0,50,50);
	glColor3f(151 / 255.0, 84 / 255.0, 23 / 255.0);
	glRectf(0, 2, 16, 12.5);
	glRectf(18, 2, 50, 12.5);
	glRectf(0, 14.5, 32, 25);
	glRectf(34, 14.5, 50, 25);
	glRectf(0, 27, 16, 37.5);
	glRectf(18, 27, 50, 37.5);
	glRectf(0, 39.5, 32, 50);
	glRectf(34, 39.5, 50, 50);
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
	int bul_x = player.x;
	int bul_y = player.y;
	int dir = player.direction;
	switch (key)
	{
	case ' ':
			if (player.itemlist[0]) {//item 발사 3개
				switch (dir) {
				case UP:
				case DOWN:
					listBullet.push_back(Bullet(dir, bul_x -1, bul_y));
					listBullet.push_back(Bullet(dir, bul_x+1, bul_y));
					break;
				case LEFT:
				case RIGHT:
					listBullet.push_back(Bullet(dir, bul_x, bul_y-1));
					listBullet.push_back(Bullet(dir, bul_x, bul_y+1));
					break;
				}
			}
			if (player.itemlist[1])//speed up
				bullet_speed = 2;
		listBullet.push_back(Bullet(dir, bul_x, bul_y));
	}
	glutPostRedisplay();
}

void timer(int value)
{
	//those shall be merged into update func
	for (list<Bullet>::iterator it = listBullet.begin(); it != listBullet.end();)//bullet management
	{
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
			int type = (*it).type;
			player.itemlist[type-1] = true;
			(*it).~Item();
			listItem.erase(it++);
		}
		else
			it++;
	}
	for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end();)//enemy management
	{
		if ((*it).bulletCollision())
		{
			(*it).~Enemy();
			listEnemy.erase(it++);
		}
		else
			it++;
	}
	//Enemy move
	if (enemy_move == 500*bullet_speed) {
		for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)//enemy management
			(*it).move();
		enemy_move = 0;
	}
	enemy_move =enemy_move + bullet_speed;
	if (player.enemyCollision())
	{
		cout << "gameover" << endl;
	}
	glutPostRedisplay();
	glutTimerFunc(bullet_speed, timer, value + 1);
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
	glutTimerFunc(10, timer, 1);
	itemInit();
	enemyInit();
	glutMainLoop();
}