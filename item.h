#pragma once
class Item
{
public:
	Item();
	~Item();
	void draw();
	int x;
	int y;
	int status; //0:in the map, 1:eaten, 2: consume
};

