#pragma once

#include <list>
#include <iterator>

class Point
{
private:
	float x;
	float y;
public:
	Point(float x, float y);
	float getX();
	float getY();
};

enum EnemyDirection {UP, DOWN, LEFT, RIGHT};

class Ghost
{
private:
	float x;
	float y;
	float z;
	float speed;
	static bool canBeEaten;
	EnemyDirection direction;

	std::list<Point *> * route;
	std::list<Point *>::iterator startPoint;
	std::list<Point *>::iterator endPoint;


public:
	Ghost();
	~Ghost();
	void update();
	void setRoute1();
	void setRoute2();
	float getX();
	float getY();
	static void setState(bool s);
	static bool getState();
	void kill();;
};