#include "item.h"
#include <GL/glut.h>
#include "player.h"
extern Player player;

Item::Item(int type, int x, int y)
{
	this->type = type;
	this->x = x;
	this->y = y;
}

Item::~Item()
{
}

void Item::draw() {//should be called only when status is 0

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	int x_fit = this->x * 50;
	int y_fit = this->y * 50;
	glTranslatef(x_fit, y_fit, 0);
	if (type == 1)
		glColor3f(1, 0.7, 0.6);
	else if (type == 2)
		glColor3f(0.6, 0.7, 1);
	glRectf(10, 10, 40, 40);
	glPopMatrix();
}

bool Item::isCollision()
{
	return (this->x == player.x) && (this->y == player.y);
}