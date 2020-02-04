#include "CentipedeManager.h"
#include "Game.h"
#include "EventSystem.h"
#include "GameEvent.h"

CentipedeManager::CentipedeManager()
{
}

void CentipedeManager::init()
{
	const auto pGame = Game::getInstance();
	const auto pGameData = pGame->getGameData();

	EventSystem::getInstance()->addListener(EventType(SEGMENT_DESTROYED_EVENT), this);

	auto pGraphicsBufferManager = pGame->getGraphicsBufferManager();
	pGraphicsBufferManager->createGraphicsBuffer(
		pGameData->getCentipedeBodyBufferKey(),
		pGameData->getAssetPath() + pGameData->getCentipedeBodyBufferFilename());
	pGraphicsBufferManager->createGraphicsBuffer(pGameData->getCentipedeHeadBufferKey(),
		pGameData->getAssetPath() + pGameData->getCentipedeHeadBufferFilename());

	CentipedeUnit* prev = nullptr;
	for (auto i = 0; i < pGameData->getInitialCentipedeLength(); i++)
	{
		const auto newCentipedeUnit = new CentipedeUnit();
		if (prev != nullptr)
		{
			newCentipedeUnit->mHead = prev;
			prev->mTail = newCentipedeUnit;
		}
		prev = newCentipedeUnit;
		mCentipedeUnits.push_back(newCentipedeUnit);
	}
	mNumSegmentsLeft = pGameData->getInitialCentipedeLength();
}

void CentipedeManager::reset()
{
	const auto initMoveSpeed = Game::getInstance()->getGameData()->getCentipedeInitMoveSpeed();
	for (auto centipedeUnit : mCentipedeUnits)
	{
		centipedeUnit->mInitMoveSpeed = initMoveSpeed;
	}
}

void CentipedeManager::cleanup()
{
	EventListener::cleanup();
	for (auto centipedeUnit : mCentipedeUnits)
	{
		delete centipedeUnit;
	}
	mCentipedeUnits.clear();
}

void CentipedeManager::respawn(bool doIncrementSpeed)
{
	const auto pGameData = Game::getInstance()->getGameData();

	CentipedeUnit* prev = nullptr;
	for (auto i = 0; i < pGameData->getInitialCentipedeLength(); i++)
	{
		mCentipedeUnits[i]->mHead = nullptr;
		mCentipedeUnits[i]->mTail = nullptr;
		if (prev != nullptr)
		{
			mCentipedeUnits[i]->mHead = prev;
			prev->mTail = mCentipedeUnits[i];
		}
		prev = mCentipedeUnits[i];

		const auto speedIncrement = doIncrementSpeed ? pGameData->getCentipedeMoveSpeedIncPerLevel() : 0;
		mCentipedeUnits[i]->respawn(speedIncrement,
			Vector2D(pGameData->getCentipedeInitSetback() + -i * mCentipedeUnits[i]->getDimensions().getX(),
				0.0f));
	}
	mNumSegmentsLeft = pGameData->getInitialCentipedeLength();
}

void CentipedeManager::physicsUpdate(float curTime)
{
	for (auto centipedeUnit : mCentipedeUnits)
	{
		centipedeUnit->physicsUpdate(curTime);
	}
}

void CentipedeManager::update(float curTime)
{
	for (auto centipedeUnit : mCentipedeUnits)
	{
		centipedeUnit->update(curTime);
	}
}

void CentipedeManager::draw()
{
	for (auto centipedeUnit : mCentipedeUnits)
	{
		centipedeUnit->draw();
	}
}

void CentipedeManager::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EventType(SEGMENT_DESTROYED_EVENT))
	{
		if (--mNumSegmentsLeft == 0)
		{
			EventSystem::getInstance()->fireEvent(Event(EventType(CENTIPEDE_KILLED_EVENT)));
		}
	}
}
