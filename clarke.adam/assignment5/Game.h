#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "Unit.h"
#include <map>
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "PerformanceTracker.h"
#include "InputTranslator.h"

// holds all systems and has the game loop
class Game : public EventListener
{
public:
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init(const Vector2D& displayDimensions, float targetFrameRate);
	void cleanup() override;

	void doLoop();

	bool getShouldExit() const { return mShouldExit; }
	System* getSystem() const { return mpSystem; }
private:
	static Game* mpsGame;

	Game();
	~Game();
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;

	void handleEvent(const Event& theEvent) override;

	void update(float curTime);
	void render();
	// exit game on esc press
	void exitGame();

	bool mIsInitted = false;

	InputTranslator* mpInputTranslator;
	System* mpSystem = nullptr;
	UnitManager* mpUnitManager = nullptr;
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;
	Timer* mpTimer = nullptr;
	PerformanceTracker* mpPerformanceTracker = nullptr;
	const std::string LOOP_TRACKER = "LOOP_TRACKER";

	bool mShouldExit = false;
	float mMsPerFrame = 60000;
	const std::string FRAME_TIME_TRACKER = "FRAME_TIME_TRACKER";
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";

	// woods background
	const std::string WOODS_FILENAME = "woods.png";
	const BufferKey WOODS_BUFFER_KEY = "WOODS";
	Sprite* mpWoodsSprite = nullptr;
	Vector2D mWoodsScale = Vector2D(1, 1);
};
#endif