#include "Sprite.h"



// This constructor is the default constructor 
// for the class
Sprite::Sprite()
{
	// Initialize all variables to their default values
	mGraphicsBuffer = new GraphicsBuffer();
	mLocation = Vector2();
	mHeight = 0;
	mWidth = 0;
}





// This constructor only takes in the asset 
// path for an bitmap and the given location for the sprite
Sprite::Sprite( string spriteFilePath, int locationX, int locationY ) 
{
	mGraphicsBuffer = new GraphicsBuffer(spriteFilePath);
	mLocation = Vector2( locationX, locationY );
	mHeight = mGraphicsBuffer->getHeight();
	mWidth = mGraphicsBuffer->getWidth();
}





// This constructor only takes a graphics buffer class and the
// given location for the sprite
Sprite::Sprite( GraphicsBuffer * newBuffer, int locationX, int locationY ) 
{
	mGraphicsBuffer = newBuffer;
	mLocation = Vector2( locationX, locationY );
	mHeight = newBuffer->getHeight();
	mWidth = newBuffer->getWidth();
}





Sprite::~Sprite()
{
}





// This function gets the current width of the sprite
int Sprite::getWidth() 
{
	return mWidth;
}





// This function gets the current length of the sprite
int Sprite::getHeight() 
{
	return mHeight;
}





// This function gets the location of the sprite
Vector2 Sprite::getLoc() 
{
	return mLocation;
}





// This function gets the Graphics Buffer class
// attached to the Sprite class
GraphicsBuffer * Sprite::getGraphicsBuffer() 
{
	return mGraphicsBuffer;
}