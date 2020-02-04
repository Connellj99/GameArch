#include "UnitManager.h"
#include "EventSystem.h"
#include "InitSmurfEvent.h"
#include "Game.h"
#include "DestroySmurfEvent.h"

UnitManager::UnitManager(GraphicsBufferManager* graphicsBufferManager)
	: mpGraphicsBufferManager(graphicsBufferManager)
{
}

UnitManager::~UnitManager()
{
	EventListener::cleanup();
}

void UnitManager::init()
{
	auto eventSystem = EventSystem::getInstance();
	eventSystem->addListener(EventType(INIT_SMURF_EVENT), this);
	eventSystem->addListener(EventType(DESTROY_SMURF_EVENT), this);
	eventSystem->addListener(EventType(SWAP_SMURF_ANIMATION_EVENT), this);
	eventSystem->addListener(EventType(TOGGLE_SMURF_ANIMATIONS_EVENT), this);

	// smurf spritesheet buffer
	mpGraphicsBufferManager->createGraphicsBuffer(SMURF_BUFFER_KEY, ASSET_PATH + SMURFS_FILENAME);
	// dean smurf spritesheet buffer
	mpGraphicsBufferManager->createGraphicsBuffer(DEAN_SMURF_BUFFER_KEY, ASSET_PATH + DEAN_SMURFS_FILENAME);
	mAnimIsDean = false;
}

void UnitManager::cleanup()
{
	clear();
	EventListener::cleanup();
}

void UnitManager::handleEvent(const Event& theEvent)
{
	switch (GameEventType(theEvent.getType()))
	{
	case INIT_SMURF_EVENT:
	{
		auto initSmurfEvent = dynamic_cast<const InitSmurfEvent&>(theEvent);
		initSmurf(initSmurfEvent.getSpawnLoc());
		break;
	}
	case DESTROY_SMURF_EVENT:
	{
		auto destroySmurfEvent = dynamic_cast<const DestroySmurfEvent&>(theEvent);
		destroyUnitsAtLoc(destroySmurfEvent.getDeleteLoc());
		break;
	}
	case SWAP_SMURF_ANIMATION_EVENT:
	{
		swapSmurfAnimation();
		break;
	}
	case TOGGLE_SMURF_ANIMATIONS_EVENT:
	{
		toggleAnimations();
		break;
	}
	default:;
	}
}

void UnitManager::initSmurf(const Vector2D& spawnLoc)
{
	Animation smurfAnimation(mpGraphicsBufferManager->getGraphicsBuffer(SMURF_BUFFER_KEY),
		SMURF_SPRITE_SIZE, SMURF_ANIMATION_SPEED_INIT, true);
	Animation deanSmurfAnimation(mpGraphicsBufferManager->getGraphicsBuffer(DEAN_SMURF_BUFFER_KEY),
		SMURF_SPRITE_SIZE, SMURF_ANIMATION_SPEED_INIT, true);
	std::map<std::string, Animation> smurfAnimations
	{
		{ SMURF_ANIMATION_NAME, smurfAnimation },
		{ DEAN_SMURF_ANIMATION_NAME, deanSmurfAnimation }
	};
	mpCurSmurfUnit = createUnit(smurfAnimations, spawnLoc - SMURF_SPRITE_SIZE * 0.5f, SMURF_SCALE);
	// set new smurf unit's initial animation to regular smurf
	mpCurSmurfUnit->setAnimation(SMURF_ANIMATION_NAME);
	mAnimIsDean = false;
}

Unit* UnitManager::createUnit(std::map<std::string, Animation>& animations, const Vector2D& initLoc,
	const Vector2D& scale)
{
	const auto unit = new Unit(animations, initLoc, scale);
	mUnits.push_back(unit);
	return unit;
}

void UnitManager::destroyUnitsAtLoc(const Vector2D& atLoc)
{
	auto unitsAtLoc = getUnitsAtLoc(atLoc);
	for (auto it = mUnits.begin(); it != mUnits.end();)
	{
		const auto i = it - mUnits.begin();
		if (unitsAtLoc[i])
		{
			if(mUnits[i] == mpCurSmurfUnit)
			{
				mpCurSmurfUnit = nullptr;
			}
			delete mUnits[i];
			it = mUnits.erase(it);
			unitsAtLoc.erase(unitsAtLoc.begin() + i);
		}
		else
		{
			++it;
		}
	}
}

void UnitManager::swapSmurfAnimation()
{
	if (mpCurSmurfUnit)
	{
		const auto newAnim = mAnimIsDean ? SMURF_ANIMATION_NAME : DEAN_SMURF_ANIMATION_NAME;
		mpCurSmurfUnit->setAnimation(newAnim);
		mAnimIsDean = !mAnimIsDean;
	}
}

void UnitManager::toggleAnimations()
{
	for (auto unit : mUnits)
	{
		unit->toggleAnimation();
	}
}

void UnitManager::clear()
{
	for (auto unit : mUnits)
	{
		delete unit;
	}
	mUnits.clear();
}

void UnitManager::update(float curTime)
{
	for (auto unit : mUnits)
	{
		unit->update(curTime);
	}
}

void UnitManager::draw()
{
	for (auto unit : mUnits)
	{
		unit->draw();
	}
}

std::vector<bool> UnitManager::getUnitsAtLoc(const Vector2D& atLoc)
{
	std::vector<bool> unitsAtLoc(mUnits.end() - mUnits.begin());
	for (auto i = 0; i < mUnits.end() - mUnits.begin(); i++)
	{
		unitsAtLoc[i] = mUnits[i]->intersects(atLoc);
	}
	return unitsAtLoc;
}

