#include "enemy.h"
#include <GL/glut.h>

Enemy::Enemy(int x, int y)
{
	this->x = x;
	this->y = y;
	this->direction = 0;
	this->nearPlayer = false;
}
void Enemy::draw()
{
	glColor3f(1.0, 0, 0);
	glRectf(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
}