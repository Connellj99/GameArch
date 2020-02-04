#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "Trackable.h"
#include "GraphicsBuffer.h"

class Sprite :public Trackable
{
private:
	GraphicsBuffer* buffer;
	int sourceX, sourceY;
	double sourceWidth, sourceHeight;
public:
	Sprite(GraphicsBuffer* currentBuffer, int x, int y, int width, int height);
	~Sprite();

	double GetWidth();
	double GetHeight();

	double GetX();
	double GetY();

	GraphicsBuffer* getBuffer();

	friend class GraphicsBuffer;

};


#endif