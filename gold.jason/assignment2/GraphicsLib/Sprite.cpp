#include "Sprite.h"

//constructors
Sprite::Sprite(){
	mBuff = nullptr;
}
Sprite::Sprite(GraphicsBuffer* buff, int LC_X, int LC_Y, int sWidth, int sHeight){
	mBuff = buff;
	mWidth = sWidth;
	mHeight = sHeight;
	LOC_X = LC_X;
	LOC_Y = LC_Y;
}

//getters
int Sprite::getLocX(){
	return LOC_X;
}

int Sprite::getLocY(){
	return LOC_Y;
}

int Sprite::getWidth(){
	return mWidth;
}

int Sprite::getHeight(){
	return mHeight;
}

GraphicsBuffer* Sprite::getBuffer(){
	return mBuff;
}

//destructor
Sprite::~Sprite(){
	delete mBuff;
}