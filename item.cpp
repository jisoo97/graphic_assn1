#include "item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::draw() {//should be called only when status is 0
	int x_fit = this->x * 50;
	int y_fit = this->y * 50;
	glColor3f(1, 0.7, 0.6);
	glRectf(x_fit+10, y_fit+10, x_fit + 40, y_fit + 40);
}
