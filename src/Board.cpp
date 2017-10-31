#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <iterator>

#include "Board.h"
#include "SOIL.h"


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
	if (!loadGLTextures())								
	{
		std::cout << "Cannot load textures" << std::endl;									
		exit(1);
	} 
	
	//left upper corner
	float x = -20;
	float y = 18;
	Field * field;

	//glBindTexture(GL_TEXTURE_2D, texture);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (fieldsMap[i][j] == 0)
			{
				field = new Field(x, y, true, false, false);
			}
			else
				field = new Field(x, y, false, true, false);

		
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

	it = fields->begin();
	(*it)->setFruit(true);
	it = fields->end();
	--it;
	(*it)->setFruit(true);
}


void Board::update()
{
	drawBackground();

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
			glColor3f(1.0, 0, 0);
			//glutSolidCube(2);
			drawCube();
		}
		if((*it)->getPoint())
		{
			glColor3f(1, 0.84, 0);
			glutSolidSphere(0.5, 10, 20);
		}
		if ((*it)->getFruit())
		{
			glColor3f(1, 1, 1);
			glutSolidSphere(0.8, 10, 20);
		}

		glTranslatef(2, 0, 0);

		if (++i == 20)
		{
			glTranslatef(-40, -2, 0);
			i = 0;
		}
	}

	glPopMatrix();
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

int Board::loadGLTextures()									// Load Bitmaps And Convert To Textures
{
	/* load an image file directly as a new OpenGL texture */
	glEnable(GL_TEXTURE_2D);
	texture = SOIL_load_OGL_texture
		(
			"../res/temple_wall.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
			);

	background = SOIL_load_OGL_texture
		(
			"../res/background.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
			);

	if (texture == 0)
		return false;

	if (background == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);

	return true;										// Return Success
}

void Board::drawCube()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Board::drawBackground()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background);

	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -40.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-25.0f, -25.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(25.0f, -25.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(25.0f, 25.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-25.0f, 25.0f, 0.0f);

	glEnd();


	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	glDisable(GL_TEXTURE_2D);
}
