class Enemy
{
public:
	int x;
	int y;
	int direction;
	bool nearPlayer;
	Enemy(int x, int y);
	void draw();
	bool wallCollision(int, int);
	bool bulletCollision();
	void move();
	bool isNearPlayer(int, int);
	int getDirectionWithNoWall(int);
	int getPlayerPartition(int, int);
};

enum direction{UP, DOWN, RIGHT, LEFT};