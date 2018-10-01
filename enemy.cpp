#include "enemy.h"
#include "player.h"
#include <cmath>
#include <GL/glut.h>

extern int map_wall[20][20];
extern int map_bullet[20][20];
extern Player player;

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

void Enemy::move() 
{
	int dist_x, dist_y,partition;
	dist_x = this->x - player.x;
	dist_y = this->y - player.y;
	if (isNearPlayer(dist_x, dist_y)) {
		partition = getPlayerPartition(dist_x, dist_y);
		getDirectionToMove();
	}
}

bool Enemy::wallCollision(int x, int y)
{
	return map_wall[x][y] == 1;
}

bool Enemy::bulletCollision()
{
	return map_bullet[this->x][this->y] == 1;
}

bool Enemy::isNearPlayer(int dist_x, int dist_y)
{
	if (abs(dist_x) <= 2 && abs(dist_y) <= 2) {//in close region
		return true;
	}
	return false;
}
int Enemy::getPlayerPartition(int dist_x, int dist_y)
{
	//UP, DOWN, RIGHT, LEFT
	int partition;
	if (dist_y < 0) {//1,2
		if (dist_x < 0) {//1 - UP, RIGHT
			partition = 1;
		}
		else {//2 - UP, LEFT
			partition = 2;
		}
	}
	else if (dist_y == 0) {//5,7
		if (dist_x > 0) partition = 5;
		else partition = 7;
	}
	else {//3,4
		if (dist_x > 0) {//3-DOWN, LEFT
			partition = 3;
			if (dist_y == 0) partition = 6;
		}
		else {//4-DOWN,RIGHT
			partition = 4;
			if (dist_y == 0) partition = 8;
		}
	}
}

int Enemy::getDirectionToMove(int partition)
{
	int direction;
	//UP, DOWN, RIGHT, LEFT
	switch (partition) {
	case 1:
		if
	case 2:
	case 3:
	case 4:
	case 5:
		direction = UP;
	case 6:
		direction = LEFT;
	case 7:
		direction = DOWN;
	case 8:
		direction = RIGHT;
	}
	int direction;
	
	if (dist_y < 0) {//1,2
		if (dist_x < 0) {//1 - UP, RIGHT
			if (ran) direction = UP;
			else direction = RIGHT;
		}
		else {//2 - UP, LEFT
			if (ran) direction = UP;
			else direction = LEFT;
		}
	}
	else if (dist_y == 0) {//Go Left or Right
		if (dist_x > 0) direction = LEFT;
		else direction = RIGHT;
	}
	else{//3,4
		if (dist_x > 0) {//3-DOWN, LEFT
			if (ran) direction = DOWN;
			else direction = LEFT;
		}
		else {//4-DOWN,RIGHT
			if (ran) direction = DOWN;
			else direction = RIGHT;
		}
	}
}


int Enemy::getDirectionWithNoWall(int partition)
{
	int diriection;
	int prev_x = this->x;
	int prev_y = this->y;
	do {
		this->x = prev_x;
		this->y = prev_y;
		diriection = (int)(rand() * 4);
		switch (diriection) {
		case UP:
			this->y = this->y + 1; break;
		case DOWN:
			this->y = this->y - 1; break;
		case RIGHT:
			this->x = this->x + 1; break;
		case LEFT:
			this->x = this->x - 1; break;
		default:
		}
	} while (!wallCollision(this->x, this->y));
}