#ifndef GAME_H
#define GAME_H

// Standard Library includes
#include <vector>

// Graphics Library includes
#include <System.h>

// Local Project includes
#include "GraphicsBufferManager.h"

#include "UnitManager.h"
#include "EventListener.h"
#include "InputTranslator.h"

// Display constant variables
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;

// Game Performance-related constant variables
const double MAX_TIME_BETWEEN_FRAMES = 16.7;

// Asset-related constant variables
const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const string DEAN_SPRITE_FILENAME = "dean_sprites.png";
const string FOREST_FILENAME = "Woods.png";
const string NAME_OF_FOREST_BUFFER = "Forest Buffer";
const string NAME_OF_SMURF_SPRITE_SHEET_BUFFER = "Smurf Sprite Sheet";
const string NAME_OF_DEAN_SMURF_SPRITE_SHEET_BUFFER = "Dean Smurf Sprite Sheet";
const double SCREEN_DIVISOR_FOR_CENTERING = 2.0;
const double BACKGROUND_SCALING_VALUE = 0.5;
const int SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_X = 25;
const int SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_Y = 25;
const int SMURFS_SPRITES_PER_ROW = 4;
const int SMURFS_SPRITES_PER_COLUMN = 4;
const int SMURF_WALK_SPEED_MODIFICATION_VALUE = 1;
const Vector2 SMURF_DIMENSIONS = Vector2(64, 60);
const Vector2 SMURF_UNIT_POSITION = Vector2(0, 0);


// Class Prototypes
class Animation;
class Unit;
class InputTranslator;


class Game : public EventListener
{
public:

	// Initializers
	void init();
	void initializeSystems();
	static void initStaticGameInstance();

	// Cleanups
	void cleanup();
	static void destroyStaticGameInstance();

	// Actions
	void doLoop();
	void flipDisplay();
	void render();

	void handleEvent(const Event& passedEvent);

	// Accessors
	static Game* getStaticInstance();
	System * getCurrentSystem();
	

private:

	// Constructors
	Game();
	Game(EventSystem* passedEventSystem);

	// Destructors
	~Game();

	// Static instances
	static Game* mpsGameObject;

	// Graphics Buffers Manager
	GraphicsBufferManager mBufferManager;

	//Unit Manager
	UnitManager * mpUnitManager;

	// Animations
	Animation * mpSmurfWalkAnimation;
	Animation * mpDeanSmurfWalkAnimation;

	// Systems
	System * mpSystem;

	// Input System
	InputSystem* mpInputSys; 

	//InputTranslator
	InputTranslator* mpInputTrans;

	// Booleans
	bool mIsDisplaying;
	bool inGame = true;
};

#endif !GAME_H

