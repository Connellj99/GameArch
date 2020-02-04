#include "PlayerUnit.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "Game.h"
#include "PlayerMoveEvent.h"

PlayerUnit::PlayerUnit()
	:Unit(Game::getInstance()->getCollisionSystem(),
		Game::getInstance()->getGameData()->getPlayerTag())
{
	const auto pGame = Game::getInstance();
	const auto pGraphicsBufferManager = pGame->getGraphicsBufferManager();
	const auto pGameData = pGame->getGameData();

	const auto pReadyBuffer = pGraphicsBufferManager->createGraphicsBuffer(
		pGameData->getPlayerReadyBufferKey(),
		pGameData->getAssetPath() + pGameData->getPlayerReadyBufferFilename());
	const auto pReloadBuffer = pGraphicsBufferManager->createGraphicsBuffer(
		pGameData->getPlayerReloadBufferKey(),
		pGameData->getAssetPath() + pGameData->getPlayerReloadBufferFilename());
	const Animation playerReadyAnim(pReadyBuffer,
		pGameData->getPlayerSpriteDimensions(), pGameData->getPlayerAnimSpeed(), true);
	const Animation playerReloadAnim(pReloadBuffer,
		pGameData->getPlayerSpriteDimensions(), pGameData->getPlayerAnimSpeed(), true);
	addAnimation(pGameData->getPlayerReadyBufferKey(), playerReadyAnim);
	addAnimation(pGameData->getPlayerReloadBufferKey(), playerReloadAnim);
	setAnimation(pGameData->getPlayerReadyBufferKey());
	setScale(pGameData->getPlayerScale());

	const auto dispDim = Game::getInstance()->getGameData()->getDisplayDimensions();
	const auto dim = getDimensions();
	mMinPlayerLoc.setY(dispDim.getY() - pGameData->getPlayerMoveRangeY());
	mMaxPlayerLoc = Vector2D(dispDim.getX() - dim.getX(), dispDim.getY() - dim.getY());

	mpBulletUnit = new BulletUnit();

	auto eventSystem = EventSystem::getInstance();
	eventSystem->addListener(EventType(PLAYER_MOVE_EVENT), this);
	eventSystem->addListener(EventType(PLAYER_SHOOT_EVENT), this);

	respawn();
}

PlayerUnit::~PlayerUnit()
{
	PlayerUnit::cleanup();
	delete mpBulletUnit;
}

void PlayerUnit::cleanup()
{
	EventListener::cleanup();
}

void PlayerUnit::physicsUpdate(float curTime)
{
	Unit::physicsUpdate(curTime);
	mpBulletUnit->physicsUpdate(curTime);
}

void PlayerUnit::handleEvent(const Event& theEvent)
{
	switch (GameEventType(theEvent.getType()))
	{
	case PLAYER_MOVE_EVENT:
	{
		// TODO: remove extra data from playermoveeventDto
		auto playerMoveEvent = dynamic_cast<const PlayerMoveEvent&>(theEvent);
		mTarLoc = playerMoveEvent.getNewLoc();
		break;
	}
	case PLAYER_SHOOT_EVENT:
	{
		playerShoot();
		break;
	}
	default:;
	}
}

void PlayerUnit::onCollision(const BoxCollision2D& collision)
{
	if (collision.getOther()->getTag() == Game::getInstance()->getGameData()->getCentipedeTag())
	{
		BoxCollider2D::setEnabled(false);
		EventSystem::getInstance()->fireEvent(Event(EventType(PLAYER_LOSE_LIFE_EVENT)));
	}
}

void PlayerUnit::update(float curTime)
{
	Unit::update(curTime);
	playerMove(mTarLoc);

	if (mIsShooting && !mpBulletUnit->getActive())
	{
		mIsShooting = false;
		setAnimation(Game::getInstance()->getGameData()->getPlayerReadyBufferKey());
	}

	mpBulletUnit->update(curTime);
}

void PlayerUnit::draw() const
{
	Unit::draw();
	mpBulletUnit->draw();
}

void PlayerUnit::respawn()
{
	setActive(true);
	setLocation(Vector2D(Game::getInstance()->getGameData()->getDisplayDimensions().getX() / 2,
		mMinPlayerLoc.getY()));
	mTarLoc = getLocation();
	mpBulletUnit->setActive(false);
}

void PlayerUnit::playerMove(const Vector2D& tarLoc)
{
	const auto playerDimensions = getDimensions();
	const auto halfPlayerDimensions = Vector2D(playerDimensions.getX() / 2.f,
		playerDimensions.getY() / 2.f);

	const auto pGame = Game::getInstance();
	const auto moveSpeed = pGame->getGameData()->getPlayerMoveSpeed();
	auto moveDir = tarLoc - getLocation() - halfPlayerDimensions;
	if (moveDir.getLength() > moveSpeed)
	{
		moveDir.normalize();
		moveDir *= moveSpeed;
	}
	auto newLoc = getLocation() + moveDir;

	// movement bounding
	if (newLoc.getY() < mMinPlayerLoc.getY())
	{
		newLoc.setY(mMinPlayerLoc.getY());
	}
	else if (newLoc.getY() > mMaxPlayerLoc.getY())
	{
		newLoc.setY(mMaxPlayerLoc.getY());
	}
	if (newLoc.getX() < mMinPlayerLoc.getX())
	{
		newLoc.setX(mMinPlayerLoc.getX());
	}
	else if (newLoc.getX() > mMaxPlayerLoc.getX())
	{
		newLoc.setX(mMaxPlayerLoc.getX());
	}
	setLocation(newLoc);
}

void PlayerUnit::playerShoot()
{
	if (mIsShooting) return;

	mIsShooting = true;
	// TODO: anim names
	setAnimation(Game::getInstance()->getGameData()->getPlayerReloadBufferKey());
	auto bulletInitLoc = getLocation();
	bulletInitLoc.setX(bulletInitLoc.getX() + getDimensions().getX() / 2.0f);
	mpBulletUnit->shoot(bulletInitLoc);
}
