#include "CentipedeUnit.h"
#include "EventSystem.h"
#include "InitMushroomEvent.h"
#include "SegmentDestroyedEvent.h"
#include "Game.h"

CentipedeUnit::CentipedeUnit()
	: Unit(Game::getInstance()->getCollisionSystem(),
		Game::getInstance()->getGameData()->getCentipedeTag())
{
	const auto pGame = Game::getInstance();
	const auto pBufferManager = pGame->getGraphicsBufferManager();
	const auto pGameData = pGame->getGameData();

	const Animation centipedeBodyAnim(
		pBufferManager->getGraphicsBuffer(pGameData->getCentipedeBodyBufferKey()),
		pGameData->getCentipedeSpriteDimensions(),
		pGameData->getCentipedeAnimSpeed(), true);
	const Animation centipedeHeadAnim(
		pBufferManager->getGraphicsBuffer(pGameData->getCentipedeHeadBufferKey()),
		pGameData->getCentipedeSpriteDimensions(),
		pGameData->getCentipedeAnimSpeed(), true);
	addAnimation(pGameData->getCentipedeBodyBufferKey(), centipedeBodyAnim);
	addAnimation(pGameData->getCentipedeHeadBufferKey(), centipedeHeadAnim);
	setAnimation(pGameData->getCentipedeBodyBufferKey());
	setScale(pGameData->getCentipedeScale());

	mInitMoveSpeed = Game::getInstance()->getGameData()->getCentipedeInitMoveSpeed();
}

CentipedeUnit::~CentipedeUnit()
{
	removeSelf();
}

void CentipedeUnit::respawn(float speedIncrement, const Vector2D& loc)
{
	const auto pGameData = Game::getInstance()->getGameData();

	setLocation(loc);
	mTarLoc = getLocation();
	setActive(true);
	mInitMoveSpeed += speedIncrement;
	mMoveSpeed = mInitMoveSpeed;
	mMoveDir = Vector2D(1, 1);
	setFlipHorizontal(false);
	if (mHead == nullptr)
	{
		setAnimation(pGameData->getCentipedeHeadBufferKey());
	}
	else
	{
		setAnimation(pGameData->getCentipedeBodyBufferKey());
	}

	doIgnoreNextMushroom = false;
	mIgnoredMushroom = nullptr;
}

void CentipedeUnit::update(float curTime)
{
	Unit::update(curTime);
	checkWallCollision();
	mTarLoc.setX(getLocation().getX() + mMoveSpeed * mMoveDir.getX());
	move();
}

void CentipedeUnit::onCollision(const BoxCollision2D& collision)
{
	const auto pGameData = Game::getInstance()->getGameData();

	const auto otherTag = collision.getOther()->getTag();
	if (otherTag == pGameData->getBulletTag())
	{
		increaseSpeedHead();
		increaseSpeedTail();
		int points;
		if (mHead)
		{
			mHead->ignoreNextMushroom();
			points = 10;
		}
		else
		{
			points = 100;
		}
		EventSystem::getInstance()->fireEvent(InitMushroomEvent(getLocation()));
		removeSelf();
		EventSystem::getInstance()->fireEvent(SegmentDestroyedEvent(points));
	}
	else if (otherTag == pGameData->getMushroomTag()
		&& abs(getLocation().getY() - mTarLoc.getY()) < 0.01f)
	{
		if (doIgnoreNextMushroom)
		{
			doIgnoreNextMushroom = false;
			mIgnoredMushroom = collision.getOther();
		}
		if (collision.getOther() == mIgnoredMushroom)
		{
			return;
		}
		mIgnoredMushroom = nullptr;

		dropSwap();
	}
}

void CentipedeUnit::increaseSpeedHead()
{
	mMoveSpeed += Game::getInstance()->getGameData()->getCentipedeMoveSpeedIncPerSplit();
	if (mHead)
	{
		mHead->increaseSpeedHead();
	}
}

void CentipedeUnit::increaseSpeedTail()
{
	mMoveSpeed += Game::getInstance()->getGameData()->getCentipedeMoveSpeedIncPerSplit();
	if (mTail)
	{
		mTail->increaseSpeedTail();
	}
}

void CentipedeUnit::dropSwap()
{
	mMoveDir.setX(mMoveDir.getX() * -1);
	flipSpriteHorizontal();
	mTarLoc.setY(mTarLoc.getY() + getDimensions().getY() * mMoveDir.getY());
}

void CentipedeUnit::checkWallCollision()
{
	auto loc = getLocation();
	auto dim = getDimensions();
	const auto pGameData = Game::getInstance()->getGameData();
	const auto dispDim = pGameData->getDisplayDimensions();

	if (mMoveDir.getX() > 0 && loc.getX() > dispDim.getX() - dim.getX()
		|| mMoveDir.getX() < 0 && loc.getX() < 0)
	{
		dropSwap();
	}
	if (mMoveDir.getY() > 0 && loc.getY() > dispDim.getY() - dim.getY() * 2
		|| mMoveDir.getY() < 0 && loc.getY() < dispDim.getY() - pGameData->getPlayerMoveRangeY())
	{
		mMoveDir.setY(mMoveDir.getY() * -1);
	}
}

void CentipedeUnit::move()
{
	auto moveDist = mTarLoc - getLocation();
	if (moveDist.getLength() > mMoveSpeed)
	{
		moveDist.normalize();
		moveDist *= mMoveSpeed;
	}
	setLocation(getLocation() + moveDist);
}

void CentipedeUnit::removeSelf()
{
	if (mHead)
	{
		mHead->mTail = nullptr;
	}
	if (mTail)
	{
		mTail->mHead = nullptr;
		mTail->setAnimation(Game::getInstance()->getGameData()->getCentipedeHeadBufferKey());
	}
	mHead = nullptr;
	mTail = nullptr;
	setActive(false);
}

void CentipedeUnit::ignoreNextMushroom()
{
	doIgnoreNextMushroom = true;
}
