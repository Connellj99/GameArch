#include "MushroomUnit.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "Game.h"

MushroomUnit::MushroomUnit(const Vector2D& initLoc)
	:Unit(Game::getInstance()->getCollisionSystem(),
		Game::getInstance()->getGameData()->getMushroomTag())
{
	const auto pGame = Game::getInstance();
	const auto pGameData = pGame->getGameData();

	const auto mushroomGraphicsBuffer = pGame->getGraphicsBufferManager()
		->getGraphicsBuffer(pGameData->getMushroomBufferKey());
	const Animation mushroomAnimation(mushroomGraphicsBuffer, pGameData->getMushroomSpriteDimesions(),
		0, false);
	addAnimation(pGameData->getMushroomBufferKey(), mushroomAnimation);
	setAnimation(pGameData->getMushroomBufferKey());
	toggleAnimation();
	setScale(pGameData->getMushroomScale());

	setLocation(initLoc);
	mHitPoints = Game::getInstance()->getGameData()->getMushroomHitPoints();
}

void MushroomUnit::onCollision(const BoxCollision2D& collision)
{
	if (collision.getOther()->getTag() == Game::getInstance()->getGameData()->getBulletTag())
	{
		mHitPoints--;
		if (mHitPoints <= 0)
		{
			EventSystem::getInstance()->fireEvent(Event(EventType(MUSHROOM_DESTROYED_EVENT)));
			setActive(false);
		}

		getCurAnimation()->increment(1);
	}
}
