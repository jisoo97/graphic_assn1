class Player
{
public:
	Player(int x, int y);
	void draw();

	int x;
	int y;
	int direction;
	int *itemlist;
	void move(int x, int y);
	bool wallCollision(int x, int y);
	bool enemyCollision(int x, int y);
	bool itemCollision(int x, int y);

};