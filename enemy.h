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
	bool isWallThere(int);
	bool bulletCollision();
	void move();
	bool isNearPlayer(int, int);
	int getDirectionWithNoWall();
	int getPlayerPartition(int, int);
	int getDirectionToMove();
};

enum direction{UP, DOWN, RIGHT, LEFT};