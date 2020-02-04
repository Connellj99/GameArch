#include "EndLevel.h"



EndLevel::EndLevel() : LevelOutline()
{
}


EndLevel::~EndLevel()
{
	cleanup();
}

//initializes the end level
void EndLevel::init(System * system, std::string level)
{
	bool mIsInit;

	LevelOutline::init(system, level);
	mpFont = new Font(ASSET_PATH + GAME_FONT, 50);
	mpMessageFont = new Font(ASSET_PATH + GAME_FONT, 20);
	mpGraphicsBufferManager = new GraphicsBufferManager();

	EventSystem::getInstance()->addListener((EventType)RESTART_EVENT, this);

	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + BACKGROUND_IMAGE, END_BUFFER_KEY);
}
//cleans up the end level
void EndLevel::cleanup()
{
	if (!mIsInit)
		return;

	EventSystem::getInstance()->removeListener((EventType)RESTART_EVENT, this);

	delete mpFont;
	delete mpMessageFont;

	delete mpGraphicsBufferManager;

	LevelOutline::cleanup();
}
//updates the end level
void EndLevel::update(double time)
{
	mpSystem->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(END_BUFFER_KEY), SCALE_FACTOR);

	drawText();
	//drawFrameRate();

	mpSystem->getGraphicsSystem()->flipDisplay();
}
//draws text on screen
void EndLevel::drawText()
{
	mpSystem->getGraphicsSystem()->writeText(400, 150, mpFont, Color(255, 255, 255), mTitleText);
	mpSystem->getGraphicsSystem()->writeText(400, 300, mpMessageFont, Color(255, 255, 255), mMessageText);
	//add score
}
//draws frame rate
void EndLevel::drawFrameRate(double frameRate)
{
	mpSystem->getGraphicsSystem()->writeText(150, 550, mpMessageFont, Color(255, 255, 255), ("FPS: " + to_string(frameRate)));
}

void EndLevel::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == GameEvents::RESTART_EVENT) 
	{
		LevelManager::getInstance()->startLevel("start");//change to level1 if it doesn't work correctly
	}
}
