#include "BulletUnit.h"
#include "Game.h"

BulletUnit::BulletUnit()
	: Unit(Game::getInstance()->getCollisionSystem(),
		Game::getInstance()->getGameData()->getBulletTag())
{
	const auto pGame = Game::getInstance();
	const auto pGameData = pGame->getGameData();
	auto graphicsBufferManager = pGame->getGraphicsBufferManager();

	const auto bulletBuffer = graphicsBufferManager->createGraphicsBuffer(
		pGameData->getBulletBufferKey(),
		pGameData->getAssetPath() + pGameData->getBulletBufferFilename());
	const Animation bulletAnim(bulletBuffer,
		pGameData->getBulletSpriteDimensions(), pGameData->getBulletAnimSpeed(), true);
	addAnimation(pGameData->getBulletBufferKey(), bulletAnim);
	setAnimation(pGameData->getBulletBufferKey());
	setScale(pGameData->getBulletScale());
	setActive(false);
}

void BulletUnit::shoot(const Vector2D& initLoc)
{
	setLocation(initLoc);
	setActive(true);
}

void BulletUnit::update(float curTime)
{
	if (!getActive()) return;

	auto loc = getLocation();
	setLocation(Vector2D(loc.getX(),
		loc.getY() - Game::getInstance()->getGameData()->getBulletMoveSpeed()));
	Unit::update(curTime);

	if (loc.getY() < 0)
	{
		setActive(false);
	}
}

void BulletUnit::onCollision(const BoxCollision2D& collision)
{
	const auto  otherTag = collision.getOther()->getTag();
	if (otherTag != Game::getInstance()->getGameData()->getPlayerTag())
	{
		setActive(false);
	}
}
