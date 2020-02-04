#pragma once
#include <string>
#include <cassert>
#include "Trackable.h"
#include "EventListener.h"
#include <vector>
#include "Sprite.h"

class Unit;
class System;
class GBuffer;
class Animation;

class UnitManager;
class GBufferManager;
class InputSystem;
class Player;
class Projectile;
class Font;

class Game : public EventListener		//The class which holds all systems and has the game loop
{
private:

	static Game* mpGameInstance;

	System *mpGameSystem;
	GBufferManager* mpBufferManager;
	UnitManager* mpUnitManager;
	
	InputSystem* mpInputSystem;
	
	Sprite* mpGameBackground;

	Animation* mpDeanSmurf;
	Animation* mpNormalSmurf;

	Player* mpPlayer;

	Font* mpFont;
	Font* mpSystemFont;

	Sprite* mpBulletSprite;
	Sprite* playerSprite;
	

	double mTargetTime;
	int mDisplayX;
	int mDisplayY;

	Game(EventSystem* pEventSystem);
	Game(double fps, EventSystem* pEventSystem);
	~Game() {};

	bool mShouldRunLoop;

	int mState = 1; //1 = Start Screen, 2 = Game, 3 = Death Screen
	bool mShouldStart = false;

	std::vector<Sprite> mMushroomSprites;
	std::vector<Sprite> mCenitSprites;
	int mScore;

	int mFPSCount;

public:

	static Game* getInstance() { assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance(double fps, EventSystem* pEventSystem) { mpGameInstance = new Game(fps, pEventSystem); };
	static void deleteInstance() { delete mpGameInstance; };

	void processInput();
	void update();
	void draw();

	int getScore() { return mScore; };
	void addScore(int amount) { mScore += amount; };

	void initGame(int x, int y, std::string filename, EventSystem* eventSystem);
	void cleanupGame();

	void handleEvent(const Event& event);

	void runGameLoop();

	void createNewCentipede(int increaseValue);

	GBufferManager* getBufferManager() { return mpBufferManager; };
	UnitManager* getUnitManager() { return mpUnitManager; };
	Player* getPlayer() { return mpPlayer; };
	std::vector<Sprite> getMushrooms() { return mMushroomSprites; };
};

