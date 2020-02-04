#ifndef GAME_H
#define GAME_H

#include "Trackable.h"
#include "System.h"
#include "Unit.h"
#include <map>
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "PerformanceTracker.h"

// holds all systems and has the game loop
class Game : public Trackable
{
public:
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init(const Vector2D& displayDimensions, float targetFrameRate);
	void cleanup();

	void doLoop();

	bool getShouldExit() const { return mShouldExit; }
	System* getSystem() const { return mpSystem; }
private:
	static Game* mpsGame;

	Game();
	~Game();
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;

	void update();
	void processInput();
	void render();

	bool mIsInitted = false;

	System* mpSystem = nullptr;
	UnitManager* mpUnitManager = nullptr;
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;
	const BufferKey BACK_BUFFER_KEY = "BACKBUFFER";
	Timer* mpTimer = nullptr;
	PerformanceTracker* mpPerformanceTracker = nullptr;
	const std::string LOOP_TRACKER = "LOOP_TRACKER";

	bool mShouldExit = false;
	float mMsPerFrame = 60000;
	const std::string FRAME_TIME_TRACKER = "FRAME_TIME_TRACKER";
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";

	// current mouse state
	MouseState mMouseState;
	// maps from key to bool of whether or not key is down
	std::map<int, bool> mKeysDown;

	// woods background
	const std::string WOODS_FILENAME = "woods.png";
	const BufferKey WOODS_BUFFER_KEY = "WOODS";
	Sprite* mpWoodsSprite = nullptr;
	Vector2D mWoodsScale = Vector2D(1, 1);

	// smurfs
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