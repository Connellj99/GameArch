#include "LevelOutline.h"
#include "EventSystem.h"


LevelOutline::LevelOutline() : EventListener(EventSystem::getInstance())
{
}


LevelOutline::~LevelOutline()
{
	cleanup();
}

void LevelOutline::init(System * system, std::string level)
{
	mIsInit = true;

	mpSystem = system;
	mLevel = level;
}

void LevelOutline::cleanup()
{
	if (!mIsInit)
		return;
}

void LevelOutline::update(double time)
{
}

void LevelOutline::reset()
{
}

void LevelOutline::drawFrameRate(double frameRate) 
{
	//mpSystem->getGraphicsSystem()->writeText(150, 550, mpMessageFont, Color(255, 255, 255), ("FPS: " + to_string(frameRate)));
}
