#ifndef GAME_H
#define GAME_H

#include "Trackable.h"
#include "System.h"
#include "Unit.h"
#include <map>

/*
For Game, make static like this
public:
	static Game* getInstance(){ assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance(){ mpGameInstance = new Game; };
	static void cleanupInstance(){ delete mpGameInstance; };
private:
	Game();

	static Game* mpGameInstance;
*/
// holds all systems and has the game loop


//game or unit manager can be alisterner
class Game : public Trackable
{
public:
	Game();
	~Game();

	void init(const Vector2D& displayDimensions, float targetFrameRate);
	void cleanup();

	void doLoop();

	bool getShouldExit() const { return mShouldExit; }
	System* getSystem() const { return mpSystem; }
private:
	Game(const Game&);
	void operator=(const Game&);

	void update();
	void processInput();
	void render();

	bool mIsInitted = false;

	System* mpSystem;
	Timer* mpTimer;

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
	const float WOODS_SCALE = 0.5f;

	GraphicsBuffer* mpWoodsBuffer;
	Sprite* mpWoodsSprite;
	Vector2D mWoodsScale = Vector2D(1, 1);

	// smurf
	const std::string SMURFS_FILENAME = "smurf_sprites.png";
	const std::string DEAN_SMURFS_FILENAME = "dean_sprites.png";
	const Vector2D SMURF_SPRITE_SIZE = Vector2D(60, 60);
	const float SMURF_ANIMATION_SPEED_INIT = 0.5f;
	const float SMURF_ANIMATION_SPEED_INCREMENT = 0.01f;
	const Vector2D SMURF_SCALE = Vector2D(1, 1);

	GraphicsBuffer* mpSmurfsBuffer;
	GraphicsBuffer* mpDeanSmurfsBuffer;
	Animation* mpSmurfAnimation;
	Animation* mpDeanSmurfAnimation;
	Unit* mpSmurfUnit;
	// true is smurf anim is dean anim, false if normal smurf anim
	bool mAnimIsDean;
};

extern Game* gpGame;

#endif