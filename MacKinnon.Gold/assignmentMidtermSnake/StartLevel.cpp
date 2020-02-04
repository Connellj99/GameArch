#include "StartLevel.h"
#include "EventSystem.h"


StartLevel::StartLevel() : LevelOutline()
{
}


StartLevel::~StartLevel()
{
	cleanup();
}
//initializes the start level
void StartLevel::init(System * system, std::string level)
{
	bool mIsInit;

	LevelOutline::init(system, level);
	mpFont = new Font(ASSET_PATH + GAME_FONT, 50);
	mpMessageFont = new Font(ASSET_PATH + GAME_FONT, 20);

	mpGraphicsBufferManager = new GraphicsBufferManager();

	EventSystem::getInstance()->addListener((EventType)START_GAME_EVENT, this);

	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + BACKGROUND_IMAGE, START_BUFFER_KEY);
}
//cleansup start level
void StartLevel::cleanup()
{
	if (!mIsInit)
		return;

	delete mpFont;
	delete mpMessageFont;
	EventSystem::getInstance()->removeListener((EventType)START_GAME_EVENT, this);

	delete mpGraphicsBufferManager;

	LevelOutline::cleanup();
}
//updates start level
void StartLevel::update(double time)
{
	mpSystem->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(START_BUFFER_KEY), SCALE_FACTOR);

	drawText();

	mpSystem->getGraphicsSystem()->flipDisplay();
}
//draws text on screen
void StartLevel::drawText()
{
	mpSystem->getGraphicsSystem()->writeText(400, 150, mpFont, Color(255, 255, 255), mTitleText);
	mpSystem->getGraphicsSystem()->writeText(400, 300, mpMessageFont, Color(255, 255, 255), mMessageText);
}
//draws frame rate
void StartLevel::drawFrameRate(double frameRate) 
{
	mpSystem->getGraphicsSystem()->writeText(150, 550, mpMessageFont, Color(255, 255, 255), ("FPS: " + to_string(frameRate)));
}

void StartLevel::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == GameEvents::START_GAME_EVENT) 
	{
		LevelManager::getInstance()->startNextLevel();
	}
}
