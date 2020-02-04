#include "HudManager.h"
#include "Game.h"

HudManager::HudManager()
{
}

HudManager::~HudManager()
{
	cleanup();
}

void HudManager::init()
{
	const auto pGame = Game::getInstance();
	pGameData = pGame->getGameData();
	pGraphicsSystem = pGame->getSystem()->getGraphicsSystem();

	mpFont = new Font(pGameData->getAssetPath() + pGameData->getFontFilename(),
		pGameData->getHudFontSize());
}

void HudManager::cleanup()
{
	delete mpFont;
	mpFont = nullptr;
}

void HudManager::draw() const
{
	const auto fontColor = pGameData->getHudFontColor();
	pGraphicsSystem->writeText(pGameData->getLevelTextLoc(), *mpFont, fontColor,
		"Lvl: " + std::to_string(mLevel));
	pGraphicsSystem->writeText(pGameData->getScoreTextLoc(), *mpFont, fontColor, "Score:" + std::to_string(mScore));
	pGraphicsSystem->writeText(pGameData->getFpsTextLoc(), *mpFont, fontColor, "FPS:" + std::to_string(mFps));
	pGraphicsSystem->writeText(pGameData->getLivesTextLoc(), *mpFont, fontColor, "<3:" + std::to_string(mLives));
}
