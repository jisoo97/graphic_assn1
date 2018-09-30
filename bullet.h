#pragma once
class Bullet
{
public:
	Bullet();
	void draw();
	void move();
	bool  isCollision();
	~Bullet();
	int x;
	int y;
	int direction; //0: up, 1:down, 2:left, 3:right
	bool destroy;
};


