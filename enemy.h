class Enemy
{
public:
	int x;
	int y;
	int direction;
	bool nearPlayer;
	Enemy(int x, int y);
	void draw();
};