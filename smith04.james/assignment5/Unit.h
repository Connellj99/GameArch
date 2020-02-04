#pragma once
#include "GraphicsLib/Animation.h"

class Unit : public Trackable
{
private:
	float x;
	float y;
	Animation* mpAnim;

public:
	Unit();
	~Unit();

	void loadAnimation(GraphicsBuffer* spriteMap, int rows, int columns);

	void update();
	void draw();
	void setAnim(Animation* newAnim);

	void setX(float xLoc);
	void setY(float yLoc);
	float getX();
	float getY();

	float getWidth();
	float getHeight();
};