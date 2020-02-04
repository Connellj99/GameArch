#include "HudUIManager.h"

HudUIManager::HudUIManager()
{
}

HudUIManager::~HudUIManager()
{
}

void HudUIManager::flipDisplay()
{
	//flip the display
	Game::getStaticInstance()->getCurrentSystem()->flipDisplay();
}

void HudUIManager::render()
{
	//draw the spawned walls, units, food and powerups
	Game::getStaticInstance()->getWallManager()->draw();
	Game::getStaticInstance()->getUnitManager()->draw();
	Game::getStaticInstance()->getFoodManager()->drawFood();
	Game::getStaticInstance()->getPowerUpManager() -> drawPowerUps();
}

void HudUIManager::renderHUD()
{
	// Draw the current level to show player what level we are in. 
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(50, 0), *Game::getStaticInstance()->getCurrentFont(), *Game::getStaticInstance()->getTitleColor(), "Level: " + to_string(Game::getStaticInstance()->getLevelManager()->getCurrentLevel()));

	// Draw the current score 
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(50, 25), *Game::getStaticInstance()->getCurrentFont(), *Game::getStaticInstance()->getTitleColor(), "Score: " + to_string(Game::getStaticInstance()->getGameScore()));

	// Draw the current fps
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(650, 0), *Game::getStaticInstance()->getCurrentFont(), *Game::getStaticInstance()->getTitleColor(), "FPS: " + to_string(Game::getStaticInstance()->getFPS()));
}

void HudUIManager::renderTitleScreen()
{
	// Draw the background image for the level
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawBackground(*Game::getStaticInstance()->getGraphicBufferManager()->getBuffer(NAME_OF_BACKGROUND_BUFFER), Game::getStaticInstance()->getBackgroundScale());

	// Draw the beginning text
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(0, 100), *Game::getStaticInstance()->getTitleFont(), *Game::getStaticInstance()->getTitleColor(), "Snake Press Space to Start");
}

void HudUIManager::renderNextLevelScreen()
{
	//draw level complete next level text
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(200, 100), *Game::getStaticInstance()->getTitleFont(), *Game::getStaticInstance()->getTitleColor(), "Level Complete!");
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(75, 150), *Game::getStaticInstance()->getTitleFont(), *Game::getStaticInstance()->getTitleColor(), "Press Space to Continue");
}

void HudUIManager::renderEndScreen()
{
	//draw game over text
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(250, 100), *Game::getStaticInstance()->getTitleFont(), *Game::getStaticInstance()->getTitleColor(), "Game Over!");
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(200, 150), *Game::getStaticInstance()->getTitleFont(), *Game::getStaticInstance()->getTitleColor(), "Escape to End!");
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(Vector2(225, 200), *Game::getStaticInstance()->getTitleFont(), *Game::getStaticInstance()->getTitleColor(), "R to Restart!");
}
