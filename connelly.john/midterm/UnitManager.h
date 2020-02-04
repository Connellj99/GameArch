#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "Unit.h"
#include "Game.h"
#include "EventListener.h"
#include "GraphicsBufferManager.h"

// holds a list of all Units in the game
class UnitManager : public EventListener
{
public:
	UnitManager(GraphicsBufferManager* graphicsBufferManager);
	~UnitManager();

	void init();
	void cleanup() override;
	void handleEvent(const Event& theEvent) override;

	void createNewUnit(std::string name, Vector2D position);

	// create smurf unit at left mouse click
	void initSmurf(const Vector2D& spawnLoc);

	void initSnake(const Vector2D& spawnLoc);

	void initFood(const Vector2D& spawnLoc);

	void initWall(const Vector2D& spawnLoc);

	void initSpeedUp(const Vector2D& spawnLoc);

	void initSlowDown(const Vector2D& spawnLoc);


	// delete smurfs at right mouse click
	void destroyUnitsAtLoc(const Vector2D& atLoc);
	// switch most recent smurf unit's animation when enter key is down

	//snake
	//void destroyObjType(string type);
	//void checkFood();
	float mFoodTime = 3000;
	void spawnFood();
	void spawnWall();
	void spawnSpeedUp();
	void spawnSlowDown();


	void swapSmurfAnimation();
	// toggle all smurfs' animations on Space
	void toggleAnimations();

	// remove and delete all units
	void clear();
	void update(float curTime);
	void draw();
private:
	GraphicsBufferManager* mpGraphicsBufferManager;
	std::vector<Unit*> mUnits;

	Unit* createUnit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale);
	std::vector<bool> getUnitsAtLoc(const Vector2D& atLoc);

	const std::string ASSET_PATH = "..\\..\\connelly.john\\midterm\\Assets\\";

	//snake config
	const std::string SNAKE_FILENAME = "snake.png";
	const BufferKey SNAKE_BUFFER_KEY = "snake";
	const Vector2D SNAKE_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey SNAKE_ANIMATION_NAME = "SNAKE";
	const float SNAKE_ANIMATION_SPEED_INIT = 0.5f;
	const Vector2D SNAKE_SCALE = Vector2D(1, 1);
	// snake head ? 
	Unit* mpCurSnakeUnit = nullptr;

	//food config
	const std::string FOOD_FILENAME = "food.png";
	const BufferKey FOOD_BUFFER_KEY = "food";
	const Vector2D FOOD_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey FOOD_ANIMATION_NAME = "FOOD";
	const float FOOD_ANIMATION_SPEED_INIT = 0.5f;
	const Vector2D FOOD_SCALE = Vector2D(1, 1);
	//ignore
	Unit* mpCurFoodUnit = nullptr;


	//wall config
	const std::string WALL_FILENAME = "wall.png";
	const BufferKey WALL_BUFFER_KEY = "wall";
	const Vector2D WALL_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey WALL_ANIMATION_NAME = "WALL";
	const float WALL_ANIMATION_SPEED_INIT = 0.5f;
	const Vector2D WALL_SCALE = Vector2D(1, 1);
	//ignore
	Unit* mpCurWallUnit = nullptr;

	//powerup speed config
	const std::string SPEEDUP_FILENAME = "speedup.png";
	const BufferKey SPEEDUP_BUFFER_KEY = "speedup";
	const Vector2D SPEEDUP_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey SPEEDUP_ANIMATION_NAME = "SPEEDUP";
	//possibly include multiple sprites like Dean smurf, to shuffle quickly through sprites to make the powerups rainbow-like 
	const float SPEEDUP_ANIMATION_SPEED_INIT = 0.5f;
	const Vector2D SPEEDUP_SCALE = Vector2D(1, 1);
	//ignore
	Unit* mpCurSpeedUpUnit = nullptr;

	//powerup slow config
	const std::string SLOWDOWN_FILENAME = "slowdown.png";
	const BufferKey SLOWDOWN_BUFFER_KEY = "slowdown";
	const Vector2D SLOWDOWN_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey SLOWDOWN_ANIMATION_NAME = "SLOWDOWN";
	//possibly include multiple sprites like Dean smurf, to shuffle quickly through sprites to make the powerups rainbow-like
	const float SLOWDOWN_ANIMATION_SPEED_INIT = 0.5f;
	const Vector2D SLOWDOWN_SCALE = Vector2D(1, 1);
	//ignore
	Unit* mpCurSlowDownUnit = nullptr;

	// smurf config
	const std::string SMURFS_FILENAME = "smurf_sprites.png";
	const std::string DEAN_SMURFS_FILENAME = "dean_sprites.png";
	const BufferKey SMURF_BUFFER_KEY = "SMURF";
	const BufferKey DEAN_SMURF_BUFFER_KEY = "DEAN";
	const Vector2D SMURF_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey SMURF_ANIMATION_NAME = "SMURF";
	const AnimKey DEAN_SMURF_ANIMATION_NAME = "DEAN";
	const float SMURF_ANIMATION_SPEED_INIT = 0.5f;
	//const float SMURF_ANIMATION_SPEED_INCREMENT = 0.01f;
	const Vector2D SMURF_SCALE = Vector2D(1, 1);

	// most recently created smurf unit
	Unit* mpCurSmurfUnit = nullptr;
	// true is smurf anim is dean anim, false if normal smurf anim
	bool mAnimIsDean = false;
};
#endif