#pragma once
#include <string>
#include <cassert>
#include "Trackable.h"
#include "EventListener.h"

class Unit;
class System;
class GBuffer;
class Animation;
class Sprite;
class UnitManager;
class GBufferManager;
class InputSystem;

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

	double mTargetTime;
	int mDisplayX;
	int mDisplayY;

	Game(EventSystem* pEventSystem);
	Game(double fps, EventSystem* pEventSystem);
	~Game();

	bool mShouldRunLoop;

public:

	static Game* getInstance() { assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance(double fps, EventSystem* pEventSystem) { mpGameInstance = new Game(fps, pEventSystem); };
	static void deleteInstance() { delete mpGameInstance; };

	void initGame(int x, int y, std::string filename, EventSystem* eventSystem);
	void cleanupGame();

	void handleEvent(const Event& event);

	void runGameLoop();

	GBufferManager* getBufferManager() { return mpBufferManager; };
	UnitManager* getUnitManager() { return mpUnitManager; };

};

