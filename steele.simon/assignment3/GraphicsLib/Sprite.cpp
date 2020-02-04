#include "Sprite.h"



// This constructor is the default constructor 
// for the class
Sprite::Sprite()
{
	// Initialize all variables to their default values
	mLocation = Vector2();
	mHeight = 0;
	mWidth = 0;
	mIsPartOfAnAnimation = false;
}





// This constructor only takes in the asset 
// path for an bitmap and the given location for the sprite
Sprite::Sprite( string spriteFilePath, int locationX, int locationY ) 
{
	mGraphicsBuffer = new GraphicsBuffer(spriteFilePath);
	mLocation = Vector2( locationX, locationY );
	mHeight = mGraphicsBuffer->getHeight();
	mWidth = mGraphicsBuffer->getWidth();
	mDisplacementX = locationX;
	mDisplacementY = locationY;
	mIsPartOfAnAnimation = false;
}





// This constructor only takes a graphics buffer class and the
// given location for the sprite
Sprite::Sprite( GraphicsBuffer * newBuffer, int locationX, int locationY, bool isPartAnimation, Vector2 dimensions) 
{
	mGraphicsBuffer = newBuffer;
	mLocation = Vector2( locationX, locationY);
	mHeight = newBuffer->getHeight();
	mWidth = newBuffer->getWidth();
	mDisplacementX = locationX;
	mDisplacementY = locationY;
	mIsPartOfAnAnimation = isPartAnimation;
	mDimensions = dimensions;
}





Sprite::~Sprite()
{
	if (mIsPartOfAnAnimation) 
	{
		delete mGraphicsBuffer;
	}
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





void Sprite::changeLoc(int newX, int newY) 
{
	mLocation.mX = newX + mDisplacementX;
	mLocation.mY = newY + mDisplacementY;
}





Vector2 Sprite::getDisplacement() 
{
	return Vector2(mDimensions.mX / 2, mDimensions.mY / 2);
}