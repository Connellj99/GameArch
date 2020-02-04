/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#pragma once
#include <chrono>
#include <stdlib.h>
#include <thread>
#include <thread>
#include <vector>
#include <string>
#include <System.h>
#include "Unit.h"
#include <Color.h>
#include <KeyCode.h>
#include <MouseCodes.h>
#include <Position.h>
#include "GraphicsBufferManager.h"
#include "UnitManager.h"


//Declare constants
extern const double SPEED_CHANGE_AMOUNT;
extern const int DISP_WIDTH;
extern const int DISP_HEIGHT;
extern const std::string ASSET_PATH;
extern const std::string SMURF_FILENAME;
extern const std::string DEAN_SMURF_FILENAME;
extern const std::string WOODS_FILENAME;
extern const std::string SAMPLE_FILENAME;

extern const float TIME_PER_SPRITE;

extern const int SMURF_SHEET_COLS;
extern const int SMURF_SHEET_HIEGHT;



/*
Define a game class. This class runs the game loop which handles input rendering etc
*/
class Game : public Trackable
{

private:
	static Game * mpsInstance; //Holds a refrince to the one and only instance of the class

	double mTimestep = 16.7;
	System * mpSystem;
	UnitManager * mpUnitManager;
	GraphicsBufferManager * mpGraphicsBufferManager;
	Timer mTheTimer;
	PerformanceTracker * mPerformanceTracker;
	std::vector<Animation * > mAnimations;

	int spriteWidth;
	int spriteHeight;
	bool mPrevousIsAnimating = true;
	bool mIsInit = false;

	/*
	Create a Game object
	*/
	Game();

	/*
	Destory the game
	*/
	~Game();

public:

	//Static members
	/*
	Initilize mpsInstance if it is not innited
	*/
	static void initInstance();

	/*
	Delete mpsInstance if it is innited
	*/
	static void cleanupInstance();

	/*
	Get mpsInstance
	*/
	static Game * getInstance();

	//Non-static members
	/*
	Initilize everything needed by game
	*/
	void init();

	/*
	Clean up all memory used
	*/
	void cleanup();

	/*
	Add a unit to the list of units in the game
	*/
	void addUnit(Unit * unit);
	
	/*
	The fixed timestep game loop that performs all actions
	*/
	void doLoop();

	/*
	Getters for the systems
	*/
	System* getSystem();

	GraphicsBufferManager * getGraphicsBufferManager();

	UnitManager * getUnitManager();
};
