#pragma once
class Item
{
public:
	Item(int type, int x, int y);
	~Item();
	void draw();
	int x;
	int y;
	int type;// subclasses
	int status; //0:in the map, 1:eaten, 2: consume
	bool isCollision();
};

