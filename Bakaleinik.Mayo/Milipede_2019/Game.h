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
class GBufferManager;
class InputSystem;

class Font;

class Game : public EventListener		//The class which holds all systems and has the game loop
{
private:

	static Game* mpGameInstance;

	System *mpGameSystem;
	GBufferManager* mpBufferManager;
	
	InputSystem* mpInputSystem;
	
	Sprite* mpGameBackground;


	Font* mpFont;
	Font* mpSystemFont;
	

	double mTargetTime;
	int mDisplayX;
	int mDisplayY;

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

	void initGame(int x, int y, EventSystem* eventSystem);
	void cleanupGame();

	void handleEvent(const Event& event);

	void runGameLoop();


	GBufferManager* getBufferManager() { return mpBufferManager; };
	std::vector<Sprite> getMushrooms() { return mMushroomSprites; };
};

