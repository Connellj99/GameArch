#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "System.h"
#include "Unit.h"
#include "Timer.h"

class Unit;
class Game;
extern Game * gpGame;

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

class Game : public Trackable
{
private:
	//System object
	System * mpSystem;

	//Other data as necessary
	GraphicsBuffer * mpWoodsBuffer;
	GraphicsBuffer * mpSmurfsBuffer;
	GraphicsBuffer * mpDeanBuffer;
	//Sprite * mpSmurfsSprite;
	//Sprite * mpDeanSprite;
	Animation * mpSmurfsAnimation;
	Animation * mpDeanAnimation;
	Unit * mpUnit;
	bool keepGoing = true;
	Timer theTimer;
	int unitLocX = CENTER_X;
	int unitLocY = CENTER_Y;
	int currentAnimation = 0;
	bool mIsInitted = false;

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
};