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

	eventSystem->addListener((EventType)CREATE_SPEEDUP, this);
	eventSystem->addListener((EventType)CREATE_SLOWDOWN, this);
	eventSystem->addListener((EventType)DESTROY_SPEEDUP, this);
	eventSystem->addListener((EventType)DESTROY_SLOWDOWN, this);
	eventSystem->addListener((EventType)CREATE_WALL, this);
	eventSystem->addListener((EventType)CREATE_FOOD, this);
	eventSystem->addListener((EventType)DESTROY_FOOD, this);
	eventSystem->addListener((EventType)MOVELEFT, this);
	eventSystem->addListener((EventType)MOVERIGHT, this);
	eventSystem->addListener((EventType)MOVEUP, this);
	eventSystem->addListener((EventType)MOVEDOWN, this);
	// smurf spritesheet buffer
	//various graphics buffers

	mpGraphicsBufferManager->createGraphicsBuffer(SMURF_BUFFER_KEY, ASSET_PATH + SMURFS_FILENAME);
	mpGraphicsBufferManager->createGraphicsBuffer(FOOD_BUFFER_KEY, ASSET_PATH + FOOD_FILENAME);
	mpGraphicsBufferManager->createGraphicsBuffer(SNAKE_BUFFER_KEY, ASSET_PATH + SNAKE_FILENAME);
	mpGraphicsBufferManager->createGraphicsBuffer(WALL_BUFFER_KEY, ASSET_PATH + WALL_FILENAME);
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
	case MOVEUP:
	{
		//change movement direction to up
		//cannot do while going down
	}
	case MOVEDOWN:
	{
		//change movement direction to down
		//canbnot do while going up
	}
	case MOVELEFT:
	{
		//change movement direction to left
		//cannot do while going right
	}
	case MOVERIGHT:
	{
		//change movement direction to right
		//cannot do while going left
	}
	case CREATE_FOOD:
	{
		spawnFood();
	}
	case CREATE_WALL:
	{
		spawnWall();
	}
	
	default:;
	}
}
void UnitManager::createNewUnit(std::string name, Vector2D position)
{
	Unit* temp = new Unit(name, position);
	mUnits.push_back(temp);
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

//Fix to allow snake/ food
void UnitManager::initSnake(const Vector2D& spawnLoc)
{
	Animation snakeAnimation(mpGraphicsBufferManager->getGraphicsBuffer(SNAKE_BUFFER_KEY),
		SNAKE_SPRITE_SIZE, SNAKE_ANIMATION_SPEED_INIT, true);
	std::map<std::string, Animation> snakeAnimations
	{
		{ SNAKE_ANIMATION_NAME, snakeAnimation },
	
	};
	mpCurSnakeUnit = createUnit(snakeAnimations, spawnLoc - SNAKE_SPRITE_SIZE * 0.5f, SNAKE_SCALE);
	mpCurSnakeUnit->setAnimation(SNAKE_ANIMATION_NAME);
}
//init food object
void UnitManager::initFood(const Vector2D& spawnLoc)
{
	Animation foodAnimation(mpGraphicsBufferManager->getGraphicsBuffer(FOOD_BUFFER_KEY),
		FOOD_SPRITE_SIZE, FOOD_ANIMATION_SPEED_INIT, true);
	std::map<std::string, Animation> foodAnimations
	{
		{ FOOD_ANIMATION_NAME, foodAnimation },

	};
	mpCurFoodUnit = createUnit(foodAnimations, spawnLoc - FOOD_SPRITE_SIZE * 0.5f, FOOD_SCALE);
	mpCurFoodUnit->setAnimation(FOOD_ANIMATION_NAME);
}
//init wall object
void UnitManager::initWall(const Vector2D& spawnLoc)
{
	Animation wallAnimation(mpGraphicsBufferManager->getGraphicsBuffer(WALL_BUFFER_KEY),
		WALL_SPRITE_SIZE, WALL_ANIMATION_SPEED_INIT, true);
	std::map<std::string, Animation> wallAnimations
	{
		{ WALL_ANIMATION_NAME, wallAnimation },

	};
	mpCurWallUnit = createUnit(wallAnimations, spawnLoc - WALL_SPRITE_SIZE * 0.5f, WALL_SCALE);
	mpCurWallUnit->setAnimation(WALL_ANIMATION_NAME);
}
//init speedup object
void UnitManager::initSpeedUp(const Vector2D& spawnLoc)
{
	Animation speedupAnimation(mpGraphicsBufferManager->getGraphicsBuffer(SPEEDUP_BUFFER_KEY),
		SPEEDUP_SPRITE_SIZE, SPEEDUP_ANIMATION_SPEED_INIT, true);
	std::map<std::string, Animation> speedupAnimations
	{
		{ SPEEDUP_ANIMATION_NAME, speedupAnimation },

	};
	mpCurSpeedUpUnit = createUnit(speedupAnimations, spawnLoc - SPEEDUP_SPRITE_SIZE * 0.5f, SPEEDUP_SCALE);
	mpCurSpeedUpUnit->setAnimation(SPEEDUP_ANIMATION_NAME);
}
//init slowdown object
void UnitManager::initSlowDown(const Vector2D& spawnLoc)
{
	Animation slowdownAnimation(mpGraphicsBufferManager->getGraphicsBuffer(SLOWDOWN_BUFFER_KEY),
		SLOWDOWN_SPRITE_SIZE, SLOWDOWN_ANIMATION_SPEED_INIT, true);
	std::map<std::string, Animation> slowdownAnimations
	{
		{ SLOWDOWN_ANIMATION_NAME, slowdownAnimation },

	};
	mpCurSlowDownUnit = createUnit(slowdownAnimations, spawnLoc - SLOWDOWN_SPRITE_SIZE * 0.5f, SLOWDOWN_SCALE);
	mpCurSlowDownUnit->setAnimation(SLOWDOWN_ANIMATION_NAME);
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


void UnitManager::spawnFood()
{
	Vector2D loc = Vector2D((rand() % 600) + 100 , (rand() % 400) + 100);
	initFood(loc);
}

void UnitManager::spawnWall()
{
	//vertical walls
	for (int i = 0; i < 650; i += 50)
	{
		Vector2D loc = Vector2D(30, i);
		initWall(loc);
	}
	for (int i = 0; i < 650; i += 50)
	{
		Vector2D loc = Vector2D(780, i);
		initWall(loc);
	}

	//horizontal walls
	for (int i = 0; i < 760; i += 50)
	{
		Vector2D loc = Vector2D(i, 30);
		initWall(loc);
	}for (int i = 0; i < 760; i += 50)
	{
		Vector2D loc = Vector2D(i, 580);
		initWall(loc);
	}
}

void spawnSpeedUp()
{
	Vector2D loc = Vector2D((rand() % 600) + 100, (rand() % 400) + 100);
	initSpeedUp(loc);
}
void spawnSlowDown()
{
	Vector2D loc = Vector2D((rand() % 600) + 100, (rand() % 400) + 100);
	initSlowDown(loc);
}
