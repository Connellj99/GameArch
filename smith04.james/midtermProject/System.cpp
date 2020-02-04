#include "System.h"

System::System(float w, float h)
{
	init(w, h);
}

System::~System()
{
	cleanup();
}

void System::init(float w, float h)
{
	mpSys = new GraphicsSystem(w, h);
	mpInSys = new InputSystem();
}

void System::cleanup()
{
	delete mpSys;
	delete mpInSys;
}

void System::draw(float x, float y, Sprite* spr, float s)
{
	mpSys->draw(x, y, spr, s);
}

void System::draw(GraphicsBuffer* target, float x, float y, Sprite* spr, float s)
{
	mpSys->draw(target, x, y, spr, s);
}

void System::writeText(float x, float y, Font* f, Color c, std::string text)
{
	mpSys->writeText(x, y, f, c, text);
}

void System::writeText(GraphicsBuffer* target, float x, float y, Font* f, Color c, std::string text)
{
	mpSys->writeText(target, x, y, f, c, text);
}

void System::flip()
{
	mpSys->flip();
}