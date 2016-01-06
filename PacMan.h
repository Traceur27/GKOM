#pragma once
#include "Board.h"
#include "Ghost.h"
#include <list>

enum Direction {NONE, NORTH, SOUTH, EAST, WEST};

class PacMan
{
private:
	float x, y, z;
	float delta;
	Direction direction;
	Direction changeDirection;
	Board * board;
	std::list<Ghost *> * ghosts;
	int score;
	int lifes;

public:
	PacMan();
	~PacMan();
	void setBoard(Board *b);
	void setGhost(Ghost * g);
	void update();
	void setDirection(Direction d);
	bool checkCollision();
	bool checkAlive();
	void tryChange(Direction d);
	void increaseScore();
	void die();
	void drawGUI();
};

