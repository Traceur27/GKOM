#include <utility>
#include <iterator>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include "PacMan.h"
#include "glut.h"
#include "Field.h"


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
		die();
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

	for (std::list<Field *>::iterator it = foundFields->begin(); it != foundFields->end(); ++it)
	{
		if ((*it)->getPoint())
		{
			increaseScore(10);
			(*it)->setPoint(false);
		}
		if ((*it)->getFruit())
		{
			increaseScore(100);
			(*it)->setFruit(false);
			Ghost::setState(true);
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
		{
			if (Ghost::getState())
			{
				(*it)->kill();
				increaseScore(100);
				return true;
			}
			return false;
		}
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

void PacMan::increaseScore(int amount)
{
	score += amount;
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
	char lifesLeft = lifes + '0';
	char scoreChar[20];
	sprintf(scoreChar, "%d", score);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glColor3f(1, 1, 1);
	
	glDisable(GL_DEPTH_TEST);
	glRasterPos2f(-0.95, -1);

	
	for (int i = 0; i < strlen(lifesText); ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lifesText[i]);
	}

	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lifesLeft);

	glRasterPos2f(0.60, -1);

	for (int i = 0; i < strlen(scoreText); ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
	}

	for (int i = 0; i < strlen(scoreChar); ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreChar[i]);
	}

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}