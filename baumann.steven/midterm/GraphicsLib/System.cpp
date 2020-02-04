#include "System.h"
#include <limits>
System::System() 
{
	//mpEventQueue = NULL;
}

System::System(int width, int height, float FPS) : mFramesPerSecond((1.0 / (float)FPS) * 1000)
{
	
	mpGraphicsSystem = new GraphicsSystem(width, height);
	//mpTimer = al_create_timer(1.0/1000);
}

void System::init() 
{
	mpGraphicsSystem->init();
	mpInSystem = new InputSystem(mpGraphicsSystem);
	
}

void System::draw(int x, int y, Sprite* picture, double scale) 
{
	mpGraphicsSystem->Draw(x, y, picture, scale);
}

void System::writeText(int x, int y, Font* font, int r, int g, int b, string text)
{
	mpGraphicsSystem->WriteText(x, y, font, r, g, b, text);
}

Animation* System::createAnimation(GraphicsBuffer* animSheet, vector<GraphicsBuffer*> &targetSheet, int dimensions) 
{
	return mpGraphicsSystem->Slice(animSheet, targetSheet, dimensions);
}

GraphicsBuffer* System::createAnimation(GraphicsBuffer* animSheet, int dimensions)
{
	return NULL;
}

void System::flip() 
{
	mpGraphicsSystem->Flip();
}

void System::waitForEvent() 
{
	mpInSystem->update();
}

int* System::getMouseState() 
{
	return mpInSystem->getMouseState();
}

void System::cleanup() 
{
	if (!mIsCleaned)
	{
		delete mpGraphicsSystem;
		delete mpInSystem;
	}
	
}

System::~System() 
{
	if (!mIsCleaned)
	{
		cleanup();
	}
}