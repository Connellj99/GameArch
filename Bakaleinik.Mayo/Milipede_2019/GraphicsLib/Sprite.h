#pragma once

#include "Trackable.h"


using namespace std;

class GBuffer;

class Sprite : public Trackable
{
public:

	
	Sprite();
	Sprite(GBuffer* name, int x, int y, int height, int width);
	

	~Sprite();

	int getSourceLocX();
	int getSourceLocY();

	int getHeight();
	int getWidth();

	GBuffer* getBuffer();



private:

	int mSpriteWidth;
	int mSpriteHeight;

	int mSource_Y;
	int mSource_X;

	GBuffer* mpSpriteBuffer = nullptr;

	
	
	

};