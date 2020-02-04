#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "System.h"
#include "Timer.h"
#include "PerformanceTracker.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"

class Unit;
class UnitManager;
class Animation;

//Game constants
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
const int CENTER_X = 400;
const int CENTER_Y = 300;
const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string WOODS_FILENAME = "Woods.png";
const string SMURFS_FILENAME = "smurf_sprites.png";
const string DEAN_FILENAME = "dean_sprites.png";
const int NUM_SMURFS = 16;
const int SMURF_COLS_ROWS = 4;
const double FPS_CONVERSION = 16.7;
const int ZERO = 0;
const float BASE_SCALE = 1.0;
const float HALF_SCALE = 0.5;
const string TRACKER = "loop";
const int SMURF_SIDE = 60;
const string WOODS_KEY = "woods";
const string SMURF_KEY = "smurf";
const string DEAN_KEY = "dean";

class Game : public Trackable
{
private:
	static Game * mpGameInstance;

	//System object
	System * mpSystem;

	//unit manager
	UnitManager * mpUnitManager;

	//graphics buffer manager
	GraphicsBufferManager * mpGBManager;

	//Other data as necessary
	//GraphicsBuffer * mpWoodsBuffer;
	//GraphicsBuffer * mpSmurfsBuffer;
	//GraphicsBuffer * mpDeanBuffer;
	
	Animation * mpSmurfsAnimation;
	Animation * mpDeanAnimation;
	//Unit * mpUnit;
	bool mKeepGoing = true;
	Timer mTheTimer;
	
	int mCurrentAnimation = 0;
	bool mIsInitted = false;
	PerformanceTracker * mpTracker;

public:
	//Constructor
	Game();

	//Destructor
	~Game();

	//Init
	void init();

	//Cleanup
	void cleanup();

	//do loop
		//get user input
		//adjust game state
		//draw current game state
	void doLoop();

	//accessor for system object
	System * getSystem() { return mpSystem; };

	//Check user inputs and do functionality
	void checkInput();

	//handles all drawing
	void render();

	//Static functions
	static Game * getInstance() { assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance() { mpGameInstance = new Game; };
	static void cleanupInstance() { delete mpGameInstance; };
};