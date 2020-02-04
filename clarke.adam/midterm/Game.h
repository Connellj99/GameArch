#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "PerformanceTracker.h"
#include "InputTranslator.h"
#include "MushroomUnitManager.h"
#include "PlayerUnit.h"
#include "CentipedeManager.h"
#include "HudManager.h"
#include "GameData.h"

enum GameState { MENU, LEVEL, END };

// holds all systems and has the game loop
class Game : public EventListener
{
public:
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init(const std::string& configFilepath);
	void cleanup() override;
	void doLoop();

	bool getShouldExit() const { return mShouldExit; }
	GameData* getGameData() const { return mpGameData; }
	System* getSystem() const { return mpSystem; }
	GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; }
	CollisionSystem* getCollisionSystem() const { return mpCollisionSystem; }
private:
	static Game* mpsGame;

	Game();
	~Game();
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;

	void handleEvent(const Event& theEvent) override;

	void physicsUpdate(float curTime);
	void update(float curTime);
	void render();
	void exitGame();

	bool mIsInitted = false;

	GameData* mpGameData = nullptr;
	InputTranslator* mpInputTranslator;
	System* mpSystem = nullptr;
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;
	Timer* mpTimer = nullptr;
	PerformanceTracker* mpPerformanceTracker = nullptr;
	const std::string LOOP_TRACKER = "LOOP_TRACKER";

	bool mShouldExit = false;
	float mMsPerFrame = 60000;
	const std::string FRAME_TIME_TRACKER = "FRAME_TIME_TRACKER";

	Font* mpFont = nullptr;
	PlayerUnit* mpPlayerUnit = nullptr;
	MushroomUnitManager* mpMushroomUnitManager = nullptr;
	CollisionSystem* mpCollisionSystem = nullptr;
	CentipedeManager* mpCentipedeManager = nullptr;
	HudManager* mpHudManager = nullptr;

	GameState mGameState = MENU;
	int mScore = 0;
	int mLevel = 1;
	int mPlayerLives = 0;
	int mPointsForExtraLife = 0;

	void initLevel();
	void respawn(bool doIncrementSpeed);
	void gameOver();
};
#endif