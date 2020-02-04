#pragma once
#include <string>
#include <cassert>
#include "Trackable.h"

class Unit;
class System;
class GBuffer;
class Animation;
class Sprite;
class UnitManager;
class GBufferManager;

class Game : public Trackable		//The class which holds all systems and has the game loop
{
private:

	static Game* mpGameInstance;

	System *mpGameSystem;
	GBufferManager* mpBufferManager;
	UnitManager* mpUnitManager;
	
	
	Sprite* mpGameBackground;

	Animation* mpDeanSmurf;
	Animation* mpNormalSmurf;

	double mTargetTime;
	int mDisplayX;
	int mDisplayY;

	Game();
	Game(double fps);
	~Game();

public:

	static Game* getInstance() { assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance(double fps) { mpGameInstance = new Game(fps); };
	static void deleteInstance() { delete mpGameInstance; };

	void initGame(int x, int y, std::string filename);
	void cleanupGame();

	

	void runGameLoop();

	GBufferManager* getBufferManager() { return mpBufferManager; };
	UnitManager* getUnitManager() { return mpUnitManager; };

};

