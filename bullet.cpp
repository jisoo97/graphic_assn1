#include "Bullet.h"
extern int map_wall[20][20];

Bullet::Bullet()
{
	destroy = false;
}


Bullet::~Bullet()
{
}

void Bullet::draw() {
	glColor3f(0.0f, 0.0f, 1.0f);
	double rad = 20;
	glBegin(GL_POLYGON);
	for (int i = 0; i<360; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = rad * cos(angle);
		double y = rad * sin(angle);
		glVertex2f(x + this->x, y + this->y);
	}
	glEnd();
}

void Bullet::move() {
	//0: up, 1:down, 2:left, 3:right
	int dir = this->direction;
	if (dir == 0) {//up
		this->y = this->y + 1;
	}
	else if(dir == 1) {//down
		this->y = this->y - 1;
	}
	else if(dir == 2) {//left
		this->x = this->x - 1;
	}
	else {//right
		this->x = this->x + 1;
	}
}

bool Bullet::isCollision() {
	int x_fit = this->x / 50;
	int y_fit = this->y / 50;
	if (map_wall[x_fit][y_fit] == 0) {//collision
		this->destroy = true;
		return true;
	}
	return false;
}