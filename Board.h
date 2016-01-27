#pragma once

#include <list>
#include <utility>
#include "Field.h"


class Board
{
private:
	static const int fieldsInRow = 20;
	static const int fieldsInColumn = 20;
	static const int fieldsMap[fieldsInRow][fieldsInColumn];
	std::list<Field *> * fields;
	std::list<Field *> * foundFields;
	int texture;
	int background;


public:
	Board();
	~Board();
	void init();
	void update();
	std::list<Field *> * findField(float x, float y);
	int loadGLTextures();
	void drawCube();
	void drawBackground();
};

