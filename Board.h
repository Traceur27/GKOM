#pragma once

#include <list>
#include "Field.h"
#include <utility>

class Board
{
private:
	static const int fieldsInRow = 20;
	static const int fieldsInColumn = 20;
	static const int fieldsMap[fieldsInRow][fieldsInColumn];
	std::list<Field *> * fields;
	std::list<Field *> * foundFields;


public:
	Board();
	~Board();
	void init();
	void update();
	std::list<Field *> * findField(float x, float y);
};

