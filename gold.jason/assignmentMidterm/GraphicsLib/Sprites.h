#ifndef Sprites_h
#define Sprites_h

#include <Trackable.h>
#include "GraphicsBuffer.h"

//dont pass by value
class Sprites:public Trackable
{
	friend class GraphicsSystem;
public:
	Sprites();
	Sprites(int height, int width, GraphicsBuffer* bufferpointer, int locX, int locY);
	~Sprites();
	int getHeight()
	{
		return mHeight;
	};
	int getWidth()
	{
		return mWidth;
	};
	int getLocX()
	{
		return mLocX;
	};
	int getLocY()
	{
		return mLocY;
	};
	GraphicsBuffer* getBuffer();

private:
	//GraphicsBuffer
	GraphicsBuffer* mpSpriteBuffer;
	//source loc
	int mLocX;
	int mLocY;
	//width and height of sprite
	int mHeight;
	int mWidth;
};
#endif // !Sprites_h