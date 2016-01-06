#include "PacMan.h"
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "Field.h"
#include <utility>
#include <iterator>
#include <iostream>


PacMan::PacMan()
{
	x = 1;
	y = -13;
	z = 1;
	delta = 0.1;
	direction = SOUTH;
	changeDirection = NONE;
	score = 0;
	lifes = 3;
	ghosts = new std::list<Ghost *>();
}


PacMan::~PacMan()
{
	for (std::list<Ghost *>::iterator it = ghosts->begin(); it != ghosts->end(); ++it)
		delete *it;
	delete ghosts;
}


void PacMan::update()
{
	if (!checkAlive())
	{
		die();
	}
	else
	{
		if (changeDirection != NONE)
			tryChange(changeDirection);

		switch (direction)
		{
		case NORTH:
			y += delta;
			if (checkCollision())
				y -= delta;
			break;
		case SOUTH:
			y -= delta;
			if (checkCollision())
				y += delta;
			break;
		case EAST:
			x += delta;
			if (checkCollision())
				x -= delta;
			break;
		case WEST:
			x -= delta;
			if (checkCollision())
				x += delta;
			break;
		}

		glPushMatrix();
		glTranslatef(x, y, z);
		glColor3f(0, 1.0, 0);
		glutSolidSphere(0.9, 20, 10);
		glPopMatrix();
	}
}

void PacMan::tryChange(Direction d)
{
	bool fail = false;
	switch (d)
	{
	case NORTH:
		y += delta;
		if (checkCollision())
		{
			y -= delta;
			fail = true;
		}
		break;
	case SOUTH:
		y -= delta;
		if (checkCollision())
		{
			y += delta;
			fail = true;
		}
		break;
	case EAST:
		x += delta;
		if (checkCollision())
		{
			x -= delta;
			fail = true;
		}
		break;
	case WEST:
		x -= delta;
		if (checkCollision())
		{
			x += delta;
			fail = true;
		}
		break;
	}
	if(!fail)
		direction = changeDirection;
}


bool PacMan::checkCollision()
{
	if (x < -19.1 || x > 19.1 || y < -19.1 || y > 19.1)
		return true;

	std::list <Field *> * foundFields = board->findField(x, y);

	//std::cout << "Pozycja pacmana: x " << x << ", y " << y << std::endl;

	for (std::list<Field *>::iterator it = foundFields->begin(); it != foundFields->end(); ++it)
	{
		 //std::cout << "Pole o wspolrzednych: x  " << (*it)->getX() << ", y  " << (*it)->getY() << std::endl;
		if ((*it)->getPoint())
		{
			increaseScore();
			(*it)->setPoint(false);
			//std::cout << "Score: " << score << std::endl;
		}

		 if ((*it)->isSolid())
			 return true;
	}

	return false;
}

bool PacMan::checkAlive()
{
	for (std::list<Ghost *>::iterator it = ghosts->begin(); it != ghosts->end(); ++it)
	{
		if (x >= (*it)->getX() - 1 && x <= (*it)->getX() + 1 && y >= (*it)->getY() - 1 && y <= (*it)->getY() + 1)
			return false;
	}
	return true;
}


void PacMan::setBoard(Board * b)
{
	board = b;
}

void PacMan::setDirection(Direction d)
{
	changeDirection = d;
}

void PacMan::increaseScore()
{
	score += 10;
}

void PacMan::setGhost(Ghost * g)
{
	ghosts->push_back(g);
}

void PacMan::die()
{
	lifes -= 1;
	if (lifes <= 0)
		exit(0);
	else
	{
		x = 1;
		y = -13;
		direction = SOUTH;
		changeDirection = NONE;
	}
}

void PacMan::drawGUI()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glPopMatrix();
}