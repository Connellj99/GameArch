#pragma once
//#include "System.h"
#include "Trackable.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
//#include "Unit.h"
#include <vector>
#include "Timer.h"

struct Input
{
	bool leftClick = false;
	bool rightClick = false;
	Vector2D clickPos = Vector2D(0, 0);
	bool fKey = false;
	bool sKey = false;
	bool escKey = false;
	bool enterKey = false;
	bool spaceKey = false;
};

class Game :public Trackable
{
public:

	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init(Vector2D screenSize, float targetFrameRate);
	void cleanup();


	void doLoop();
	bool checkIfStillLoop() { return mLoopGame; }
	
	System* getSystem();

private:
	Game();
	~Game();

	static Game* mpsGameInstance;
	GraphicsBufferManager mBufferManager;
	UnitManager mUnitManager;


	Input checkInput();
	void render();
	void update(Input input);

	System *mSystem;
	Timer mTimer;
	double mframeTime;
	Vector2D mScreenSize;

	//Loop info
	bool mLoopGame = true;
	
	//Sprites & Animations
	const double SPEED_CHANGE = 50;

	const string SMURF_FILENAME = "smurf_sprites.png";
	const string DEAN_FILENAME = "dean_sprites.png";
	//Map Keys
	const string SMURF_KEY = "SmurfSheet";
	const string DEAN_KEY = "DeanSheet";
	const string WOODS_KEY = "Woods";

	const string BACKGROUND_FILENAME = "woods.png";
	const float WOODS_SCALE = 0.5f;
	Sprite* mpWoodsSprite;

	//Basic Info
	const string MILLER_FILE_PATH = "..\\..\\Roman.Miller\\assignment2\\";
	const string SHARED_PATH = "..\\..\\shared\\assets\\";

	const Vector2D SMURFS_LAYOUT= Vector2D(4, 4);
	const Vector2D SMURF_SPRITE_SIZE = Vector2D(60, 60);

	const string TRACKER = "Loop_Time";

};
