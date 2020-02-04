#pragma once

#include "../Header.h"
#include "../GraphicsBuffer.h"

class Sprite : public Trackable
{
private:
	GraphicsBuffer* mpGraphicsBuffer;
	float xloc;
	float yloc;
	float width;
	float height;

public:
	Sprite();
	Sprite(float x, float y, float w, float h, GraphicsBuffer* buff);
	~Sprite();
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	GraphicsBuffer* getBuffer();

	void draw(float x, float y);
};