/*
   Computer graphics assignment 1

   20150309 ��ǻ�Ͱ��а� ������
   20150863 ��ǻ�Ͱ��а� ������  
*/
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
Player player(10, 10);
list<Bullet> listBullet;//list for managing bullet objects.
list<Enemy> listEnemy;//list for managing enemy objects
list<Item> listItem;// list for managing item objects.

//maps
extern int map_wall[20][20];
extern int map_enemy[20][20];
extern int map_bullet[20][20];
extern int map_item[20][20];


int enemy_move = 0;
int bullet_speed = 4;
bool game_over = false;
int width = 500;
int height = 400;
bool once = true;

// function called when the window size is changed
void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);// modifying viewport as window size changes
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(player.x * 50 - 250, player.x * 50 + 250, player.y * 50 - 200, player.y * 50 + 200);// to make a player always be in the middle of the window
	glTranslatef(50, 0, 0); 
}

// function for printing text
// reference : http://programmingexamples.net/wiki/OpenGL/Text 
void printtext(int x, int y, string String)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 300, 0, 300);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	for (int i = 0; i<String.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

// function for drawing a wall cell
void drawWall(int i, int j)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(i * 50, j * 50, 0);
	glColor3f(86 / 255.0, 52 / 255.0, 27 / 255.0);
	glRectf(0, 0, 50, 50);
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

// function that draws a status bar below the screen
void drawStatusBar()
{
	glViewport(0, 0, width, height / 5);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 100);
	glColor3f(0.3, 0.3, 0.3);
	glRectf(0, 0, 500, 100);


	glColor3f(0, 0, 0);
	printtext(210, 250, "item list");
	if (player.itemlist[0]) // when player got an item1
		printtext(210, 150, "three bullets");

	if (player.itemlist[1]) // when the player got item2
		printtext(210, 100, "speed up bullets");

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

// function to make screen follow the player.
// the screen is restricted to the boundaries of the map.
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


void display()
{

	if (!game_over) { // if game is not over.
		glViewport(0, height / 5, width, height * 4 / 5); // upper part of the viewport
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		cameraMove();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < 20; i++) // draw walls
			for (int j = 0; j < 20; j++)
				if (map_wall[i][j])
					drawWall(i, j);
		for (list<Bullet>::iterator it = listBullet.begin(); it != listBullet.end(); it++) // draw bullets
			(*it).draw();
		for (list<Item>::iterator it = listItem.begin(); it != listItem.end(); it++)// draw items
			(*it).draw();
		for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++) //draw enemies
			(*it).draw();
		player.draw(); // draw player
		drawStatusBar();
		glutSwapBuffers();
		
	}
	// if the game is over(all enemies are defeated or player touched an enemy)
	else {
		if (once) {
			glViewport(0, 0, width, height);
			printtext(140, 180, "Gameover"); once = false;
			glutSwapBuffers();
		}
	}//drawStatusBar();
	//glutSwapBuffers();
}

// function that describes the effects of pushing arrow keys.
void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		player.move(player.x, player.y + 1);
		break;
	case GLUT_KEY_DOWN:
		player.move(player.x, player.y - 1);
		break;
	case GLUT_KEY_LEFT:
		player.move(player.x - 1, player.y);
		break;
	case GLUT_KEY_RIGHT:
		player.move(player.x + 1, player.y);
		break;
	}
	cameraMove();
	glutPostRedisplay();
}

// function called when bullet is fired. (space bar)
void keyboard(unsigned char key, int x, int y)
{
	int bul_x = player.x;
	int bul_y = player.y;
	int dir = player.direction;
	switch (key)
	{
	case ' ':// space bar has been pushed.
		// item1: 3 bullets are fired simultaneously.
		if (player.itemlist[0]) {
			
			switch (dir) {
			case UP:
			case DOWN:
				listBullet.push_back(Bullet(dir, bul_x - 1, bul_y));
				listBullet.push_back(Bullet(dir, bul_x + 1, bul_y));
				break;
			case LEFT:
			case RIGHT:
				listBullet.push_back(Bullet(dir, bul_x, bul_y - 1));
				listBullet.push_back(Bullet(dir, bul_x, bul_y + 1));
				break;
			}
		}
		// item2: speed up bullets.
		if (player.itemlist[1])
			bullet_speed = 2;
		listBullet.push_back(Bullet(dir, bul_x, bul_y));
	}
	glutPostRedisplay();
}

// timer function for updating the status of objects.
void timer(int value)
{
	for (list<Bullet>::iterator it = listBullet.begin(); it != listBullet.end();)//bullet management
	{
		(*it).move();
		if ((*it).wallCollision())// when a bullet reached to wall, it disappears.
		{
			(*it).~Bullet();
			listBullet.erase(it++);
		}
		else
			it++;
	}

	for (list<Item>::iterator it = listItem.begin(); it != listItem.end();)//item management
	{
		if ((*it).playerCollision()) // player got an item
		{
			int type = (*it).type;
			player.itemlist[type - 1] = true;
			(*it).~Item();
			listItem.erase(it++);
		}
		else
			it++;
	}
	for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end();)//enemy management
	{
		if ((*it).bulletCollision()) // when an enemy got fired, it disappears.
		{
			(*it).~Enemy();
			listEnemy.erase(it++);
		}
		else
			it++;
	}
	//Enemy moves periodically. (enemy move is a kind of timer)
	if (enemy_move == 500 * bullet_speed) {
		for (list<Enemy>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)//enemy management
			(*it).move();
		enemy_move = 0;
	}
	enemy_move = enemy_move + bullet_speed;// enemy move timer update

	//Game over check
	if (player.enemyCollision() || listEnemy.empty())
		game_over = true;
	glutPostRedisplay();
	glutTimerFunc(bullet_speed, timer, value + 1);
}

// function that reads map_item and creates the objects.
void init()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			if (map_item[i][j] != 0) // creates item objects
				listItem.push_back(Item(map_item[i][j], i, j));
			if (map_enemy[i][j] != 0) // creates enemy objects
				listEnemy.push_back(Enemy(i, j));
		}
}


void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("simple");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(10, timer, 1);
	init();
	glutMainLoop();
}