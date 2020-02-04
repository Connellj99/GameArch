#pragma once
#include "Vector2D.h"
#include "GraphicsBuffer.h"

class Sprite : public Trackable
{
	friend class GraphicsSystem;
private:
	GraphicsBuffer* gBuffer;
	int mlocX;
	int mlocY;
	int spriteWidth;
	int spriteHight;
public:
	Sprite(int locX, int locY, int mHeight, int mWidth, GraphicsBuffer* gBuffer);
	~Sprite();
	int getLocX() { return mlocX; };
	int getLocY() { return mlocY; };
	int getSpriteWidth() { return spriteWidth; };
	int getSpriteHeight() { return spriteHight; };
	GraphicsBuffer* getGraphicsBuffer() { return gBuffer; };
};