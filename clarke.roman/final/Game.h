#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "Unit.h"
#include <map>
#include "GraphicsBufferManager.h"
#include "PerformanceTracker.h"
#include "InputTranslator.h"
#include "PlayerUnit.h"

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

	//Scene Index
	int mSceneIndex = 0;

	//Font and colors
	Font* mpFont = nullptr;
	const Color PINK = Color(255, 20, 215, 255);

	InputTranslator* mpInputTranslator;
	System* mpSystem = nullptr;
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;
	Timer* mpTimer = nullptr;
	PerformanceTracker* mpPerformanceTracker = nullptr;
	const std::string LOOP_TRACKER = "LOOP_TRACKER";

	bool mShouldExit = false;
	float mMsPerFrame = 60000;
	const std::string FRAME_TIME_TRACKER = "FRAME_TIME_TRACKER";
	const std::string ASSET_PATH = "..\\..\\clarke.roman\\final\\assets\\";

	//Font Filename
	const std::string FONT_FILENAME = "cour.ttf";

	// woods background
	const std::string WOODS_FILENAME = "woods.png";
	const BufferKey WOODS_BUFFER_KEY = "WOODS";
	Sprite* mpWoodsSprite = nullptr;
	Vector2D mWoodsScale = Vector2D(1, 1);

	// player
	PlayerUnit* mpPlayerUnit = nullptr;
	std::string mPlayerSkateFilename = "player_skate.png";
	BufferKey mPlayerSkateBufferKey = "PLAYER_SKATE";
	Vector2D smurfSpriteDim = Vector2D(60, 60);
	float smurfAnimSpeed = 1.0f;
	Vector2D smurfScale = Vector2D(1, 1);
};
#endif