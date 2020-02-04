#include "MushroomUnitManager.h"
#include "Event.h"
#include "GameEvent.h"
#include "EventSystem.h"
#include "Game.h"
#include "InitMushroomEvent.h"

MushroomUnitManager::MushroomUnitManager()
{
}

MushroomUnitManager::~MushroomUnitManager()
{
	MushroomUnitManager::cleanup();
}

void MushroomUnitManager::init()
{
	const auto pGame = Game::getInstance();
	const auto pGameData = pGame->getGameData();

	auto eventSystem = EventSystem::getInstance();
	eventSystem->addListener(EventType(INIT_MUSHROOM_EVENT), this);

	pGame->getGraphicsBufferManager()->createGraphicsBuffer(pGameData->getMushroomBufferKey(),
		pGameData->getAssetPath() + pGameData->getMushroomBuffferFilename());

	srand(time(nullptr));

	reset();
}

void MushroomUnitManager::reset()
{
	clear();
	const auto numInitMushrooms = Game::getInstance()->getGameData()->getNumInitMushrooms();
	for (auto i = 0; i < numInitMushrooms; i++)
	{
		mMushroomUnits.push_back(new MushroomUnit(getRandLoc()));
	}
}

void MushroomUnitManager::cleanup()
{
	clear();
	EventListener::cleanup();
}

void MushroomUnitManager::handleEvent(const Event& theEvent)
{
	if (GameEventType(theEvent.getType()) == INIT_MUSHROOM_EVENT)
	{
		const auto& initMushroomEvent = dynamic_cast<const InitMushroomEvent&>(theEvent);
		mMushroomUnits.push_back(new MushroomUnit(initMushroomEvent.getInitLoc()));
	}
}

bool MushroomUnitManager::intersectsAny(const Vector2D& atLoc)
{
	for (auto mushroomUnit : mMushroomUnits)
	{
		if (mushroomUnit->intersects(atLoc))
		{
			return true;
		}
	}
	return false;
}

void MushroomUnitManager::physicsUpdate(float curTime)
{
	for (auto mushroomUnit : mMushroomUnits)
	{
		mushroomUnit->physicsUpdate(curTime);
	}
}

void MushroomUnitManager::update(float curTime)
{
	for (auto mushroomUnit : mMushroomUnits)
	{
		mushroomUnit->update(curTime);
	}
}

void MushroomUnitManager::draw()
{
	for (auto mushroomUnit : mMushroomUnits)
	{
		mushroomUnit->draw();
	}
}

Vector2D MushroomUnitManager::getRandLoc()
{
	const auto pGameData = Game::getInstance()->getGameData();
	const auto mushroomSpriteDimesions = pGameData->getMushroomSpriteDimesions();
	const auto boundsDimensions = pGameData->getDisplayDimensions()
		- mushroomSpriteDimesions;

	const auto x = mushroomSpriteDimesions.getX() + rand() % int(boundsDimensions.getX() - mushroomSpriteDimesions.getX() * 2);
	const auto y = mushroomSpriteDimesions.getY() + rand() % int(boundsDimensions.getY() - pGameData->getPlayerMoveRangeY());
	return Vector2D(x, y);
}

void MushroomUnitManager::clear()
{
	for (auto mushroomUnit : mMushroomUnits)
	{
		delete mushroomUnit;
	}
	mMushroomUnits.clear();
}
