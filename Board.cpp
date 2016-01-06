#include "Board.h"
#include "Field.h"
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iterator>
#include <iostream>


const int Board::fieldsMap[fieldsInRow][fieldsInColumn] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
};


Board::Board()
{
	fields = new std::list<Field *>();
	foundFields = new std::list<Field *>();
}

Board::~Board()
{
	delete fields;
	delete foundFields;
}

void Board::init()
{
	//left upper corner
	float x = -20;
	float y = 18;
	Field * field;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (fieldsMap[i][j] == 0)
			{
				field = new Field(x, y, true, false);
			}
			else
				field = new Field(x, y, false, true);

			//std::cout << "wspolrzedne pola [" << i << "][" << j << "] = " << x << ", " << y << std::endl;
		
			fields->push_back(field);
			x += 2;
		}

		x -= 40;
		y -= 2;
	}

	std::list<Field *>::iterator it = fields->begin();
	int k;
	for (k = 0; k < 169; k++, it++);
	(*it)->setPoint(false);
	++it;
	(*it)->setPoint(false);
	for (k = 0; k < 19; k++, it++);
	(*it)->setPoint(false);
	++it;
	(*it)->setPoint(false);
}


void Board::update()
{
	glColor3f(1.0, 0.0, 0.0);

	//floor
	glBegin(GL_QUADS);
	glVertex3f(20, -20, 0);
	glVertex3f(20, 20, 0);
	glVertex3f(-20, 20, 0);
	glVertex3f(-20, -20, 0);
	glEnd();

	glColor3f(0, 0, 1.0);

	//moving to the left upper corner
	glPushMatrix();
	glTranslatef(-19, 19, 1);
	int i = 0;
	for (std::list<Field *>::iterator it = fields->begin(); it != fields->end(); ++it)
	{
		if((*it)->isSolid())
		{
			glColor3f(0, 0, 1.0);
			glutSolidCube(2);
		}
		if((*it)->getPoint())
		{
			glColor3f(1, 0.84, 0);
			glutSolidSphere(0.5, 10, 20);
		}
		glTranslatef(2, 0, 0);

		if (++i == 20)
		{
			glTranslatef(-40, -2, 0);
			i = 0;
		}
	}

	glPopMatrix();

	//glPushMatrix();
	////moving to the left upper corner4
	//glTranslatef(-19, 19, 1);
	//glColor3f(0, 0, 1.0);

	////fields
	//for (int i = 0; i < fieldsInRow; ++i)
	//{
	//	for (int j = 0; j < fieldsInColumn; ++j)
	//	{
	//		if (fieldsMap[i][j] == 0)
	//		{
	//			glutSolidCube(2);
	//		}
	//		glTranslatef(2, 0, 0);
	//	}

	//	glTranslatef(-40, -2, 0);
	//}

	//glPopMatrix();
}


std::list<Field *> * Board::findField(float x, float y)
{
	foundFields->clear();

	for (std::list<Field *>::iterator it = fields->begin(); it != fields->end(); ++it)
	{
		if ((*it)->conteins(x, y))
			foundFields->push_back(*it);

		if (foundFields->size() == 4)
			break;
	}

	return foundFields;
}