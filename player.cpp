#include "player.h"
#include <GL/glut.h>
#include <algorithm>
extern int map_wall[20][20];
extern int map_enemy[20][20];
extern int map_item[20][20];
using namespace std;

extern Player player;
Player::Player(int x, int y) {
	this->x = x;
	this->y = y;
	this->direction = 0;//0:up, 1:down, 2:left, 3:right
	this->itemlist = (int *)malloc(2 * sizeof(int));//item inventory can hold 2 items
}

void Player::draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	//glRotatef(45, 1, 0, 0);
	glTranslatef(x*50, y*50, 0);
	glColor3f(91/255.0, 155/255.0, 213/255.0);
	glRectf(0,0,50,50);
	glPopMatrix();
	
	//glRectf(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
}

void Player::move(int x, int y)
{

	if (x == (this->x + 1))
		this->direction = 3;
	else if (x == (this->x - 1))
		this->direction = 2;
	else if (y == (this->y + 1))
		this->direction = 0;
	else
		this->direction = 1;

	if (!this->wallCollision(x, y))
	{
		this->x = x;
		this->y = y;
	}


	
	
}

bool Player::wallCollision(int x, int y)
{
	return map_wall[x][y] == 1;
}

bool Player::enemyCollision(int x, int y)
{
	return map_enemy[x][y] == 1;
}

bool Player::itemCollision(int x, int y)
{
	return map_item[x][y] == 1;
}