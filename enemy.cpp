#include "enemy.h"
#include "player.h"
#include <cmath>
#include <GL/glut.h>

extern int map_wall[20][20];
extern int map_bullet[20][20];
extern int map_enemy[20][20];
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
	int direction, prev_x, prev_y;
	prev_x = this->x;
	prev_y = this->y;
	direction = getDirectionToMove();
	switch(direction) {
	case UP:
		this->y = this->y + 1;
	case DOWN: 
		this->y = this->y - 1;
	case LEFT:
		this->x = this->x - 1;
	case RIGHT:
		this->x = this->x + 1;
	}
	map_enemy[prev_x][prev_y] = 0;
	map_enemy[this->x][this->y] = 1;
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

bool Enemy::isWallThere(int direction) {//check if there is wall in certain direction
	int new_x = this->x;
	int new_y = this->y;
	switch (direction) {
	case UP: new_y++; break;
	case DOWN: new_y--; break;
	case RIGHT: new_x++; break;
	case LEFT: new_x--; break;
	}
	return wallCollision(new_x, new_y);
}

int Enemy::getDirectionToMove()//return Direction according to partition
{
	int dist_x, dist_y, partition, direction;
	dist_x = this->x - player.x;
	dist_y = this->y - player.y;
	if (!isNearPlayer(dist_x, dist_y)) {//far from player
		direction = getDirectionWithNoWall();
	}
	else {//near player
		partition = getPlayerPartition(dist_x, dist_y);
		//UP, DOWN, RIGHT, LEFT
		switch (partition) {
		case 1://up, right
			direction = UP;
			if (isWallThere(direction))
				direction = RIGHT;
			break;
		case 2://up, left
			direction = LEFT;
			if (isWallThere(direction))
				direction = UP;
			break;
		case 3://down, left
			direction = DOWN;
			if (isWallThere(direction))
				direction = LEFT;
			break;
		case 4://down, right
			direction = RIGHT;
			if (isWallThere(direction))
				direction = DOWN;
			break;
		case 5:
			direction = UP; break;
		case 6:
			direction = LEFT; break;
		case 7:
			direction = DOWN; break;
		case 8:
			direction = RIGHT; break;
		}
		if (isWallThere(direction))
			direction = getDirectionWithNoWall();
	}
}


int Enemy::getDirectionWithNoWall() //Return direction with no Wall
{
	int direction;
	int prev_x = this->x;
	int prev_y = this->y;
	do {
		this->x = prev_x;
		this->y = prev_y;
		direction = (int)(rand() * 4);
		switch (direction) {
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
	return direction;
}
