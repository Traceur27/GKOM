#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "Ghost.h"


bool Ghost::canBeEaten = false;

Ghost::Ghost()
{
	z = 1;
	speed = 0.3;
	route = new std::list<Point *>();
}


Ghost::~Ghost()
{
	for (startPoint = route->begin(); startPoint != route->end(); ++startPoint)
		delete *startPoint;

	delete route;
}

void Ghost::update()
{
	if ((x >= (*endPoint)->getX() - speed && x <= (*endPoint)->getX() + speed)&& 
		(y >= (*endPoint)->getY() - speed && y <= (*endPoint)->getY() + speed))
	{
		x = (*endPoint)->getX();
		y = (*endPoint)->getY();

		startPoint++;
		endPoint++;

		if (endPoint == route->end())
		{
			endPoint = route->begin();
			startPoint = endPoint++;
		}

		if ((*endPoint)->getX() == (*startPoint)->getX()) // same x, we're mowing vertically
		{
			if ((*endPoint)->getY() > (*startPoint)->getY())
				direction = UP;
			else
				direction = DOWN;
		}
		else if ((*endPoint)->getY() == (*startPoint)->getY()) //same y, we're moving horizontally
		{
			if ((*endPoint)->getX() > (*startPoint)->getX())
				direction = RIGHT;
			else
				direction = LEFT;
		}
	}

	switch (direction)
	{
	case UP:
		y += speed;
		break;
	case DOWN:
		y -= speed;
		break;
	case RIGHT:
		x += speed;
		break;
	case LEFT:
		x -= speed;
		break;
	}

	glPushMatrix();
	glTranslatef(x, y, z);
	
	if (canBeEaten)
		glColor4f(0.5, 0.5, 0.5, 0.7);
	else
		glColor3f(0.5, 0.5, 0.5);
	
	glutSolidSphere(0.9, 20, 10);
	glPopMatrix();
}

void Ghost::setRoute1()
{
	x = -1;
	y = 1;
	route->clear();
	route->push_back(new Point(-1, 1));
	route->push_back(new Point(-1, 5));
	route->push_back(new Point(-19, 5));
	route->push_back(new Point(-19, 19));
	route->push_back(new Point(-15, 19));
	route->push_back(new Point(-15, 9));
	route->push_back(new Point(-9, 9));
	route->push_back(new Point(-9, 15));
	route->push_back(new Point(3, 15));
	route->push_back(new Point(3, 19));
	route->push_back(new Point(19, 19));
	route->push_back(new Point(19, 5));
	route->push_back(new Point(-1, 5));
	route->push_back(new Point(-1, 1));

	endPoint = route->begin();
	startPoint = endPoint++;
	direction = UP;
}

void Ghost::setRoute2()
{
	x = 1;
	y = 1;
	route->clear();
	route->push_back(new Point(1, 1));
	route->push_back(new Point(1, 5));
	route->push_back(new Point(5, 5));
	route->push_back(new Point(5, -3));
	route->push_back(new Point(9, -3));
	route->push_back(new Point(9, -7));
	route->push_back(new Point(11, -7));
	route->push_back(new Point(11, -15));
	route->push_back(new Point(15, -15));
	route->push_back(new Point(15, -9));
	route->push_back(new Point(19, -9));
	route->push_back(new Point(19, -19));
	route->push_back(new Point(7, -19));
	route->push_back(new Point(7, -13));
	route->push_back(new Point(-7, -13));
	route->push_back(new Point(-7, -19));
	route->push_back(new Point(-19, -19));
	route->push_back(new Point(-19, -5));
	route->push_back(new Point(-9, -5));
	route->push_back(new Point(-9, 5));
	route->push_back(new Point(1, 5));
	route->push_back(new Point(1, 1));


	endPoint = route->begin();
	startPoint = endPoint++;
	direction = UP;
}

float Ghost::getX()
{
	return x;
}

float Ghost::getY()
{
	return y;
}


void myTimer(int value)
{
	Ghost::setState(false);
}


void Ghost::setState(bool s)
{
	if (s)
	{
		glutTimerFunc(10000, myTimer, 0);
	}
	canBeEaten = s;
}

bool Ghost::getState()
{
	return canBeEaten;
}

void Ghost::kill()
{
	if (rand() % 2)
		setRoute1();
	else
		setRoute2();
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Point::getX()
{
	return x;
}

float Point::getY()
{
	return y;
}
