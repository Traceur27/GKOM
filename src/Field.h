#pragma once
class Field
{
private:
	float positionX;
	float positionY;
	bool solid;
	bool containPoint;
	bool fruit;

public:
	Field(float x, float y, bool s, bool c, bool f);
	~Field();
	bool conteins(float x, float y);
	float getX();
	float getY();
	bool isSolid();
	bool getPoint();
	void setPoint(bool s);
	bool getFruit();
	void setFruit(bool f);
};

