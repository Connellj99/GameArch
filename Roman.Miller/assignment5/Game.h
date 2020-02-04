#pragma once
#include "Trackable.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "EventListener.h"
#include "InputTranslator.h"
#include "InputSystem.h"
#include <vector>
#include "Timer.h"
using namespace std;

class Game : public EventListener
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
	InputSystem* mpInputSystem;
	InputTranslator* mpInputTranslator;


	//Mangers
	GraphicsBufferManager mBufferManager;
	UnitManager mUnitManager;

	//Event System Classes

	//Change check input to  call inut system udate
	//that fires events and then you dot need to keep checking
	// fair game to call funtions from input system in game

	void render();
	void update();

	System *mSystem;
	Timer mTimer;
	double mframeTime;
	Vector2D mScreenSize;

	//This does not allow copies of the Game, only passes by referance or gives liker error
	Game(Game& game)=delete; // this should never have deffinition as it was deleted, compilerwill stop and not allow you to copy as constutor has been invialidated
	void operator=(const Game& game);

	//Funtion for on event triggers
	void handleEvent(const Event& theEvent);
	void createNewUnit(Vector2D loc);
	void deleteUnitAtLoc(Vector2D loc);
	void pauseAllAnimation();
	void swapAnimationOfLastUnit();
	void exitDoloop();


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
