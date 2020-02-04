#ifndef GAME_H
#define GAME_H

// Standard Library includes
#include <vector>

// Graphics Library includes
#include <System.h>

#include <assert.h>

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
const double SCREEN_DIVISOR_FOR_CENTERING = 2.0;
const double BACKGROUND_SCALING_VALUE = 0.5;
const int SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_X = -120;
const int SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_Y = -120;
const int SMURFS_SPRITES_PER_ROW = 4;
const int SMURFS_SPRITES_PER_COLUMN = 4;
const int SMURF_WALK_SPEED_MODIFICATION_VALUE = 1;
const Vector2 SMURF_DIMENSIONS = Vector2(64, 60);
const Vector2 SMURF_UNIT_POSITION = Vector2(0, 0);

// Class Prototypes
class Animation;
class Unit;
class UnitManager;
class GraphicsBufferManager;

class Game : public Trackable
{

public:
	//static game instance setters
	static Game* getInstance() { assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance() { mpGameInstance = new Game; };
	static void cleanupInstance() { delete mpGameInstance; };

	// Destructors
	~Game();

	// Initializers
	void init();
	void initializeSystems();

	// Cleanups
	void cleanup();//cleans the managers
	void cleanExtra();//cleans extra unit buffers or animations and sprites

	// Mutators
	void addBackgroundImage( Sprite& newBackground );
	void DoLoop();
	void addUnit( Unit newUnit );
	void flipDisplay();
	void render();
	void centerToScreen( Unit& unitToBeCentered );
	
	// Acessors
	System * getCurrentSystem();
	UnitManager* getUnitManager();

private:
	Game();
	Game(double newTimeBetweenFrames);

	static Game* mpGameInstance;

	//Inputs
	Mouse_State mMouseInput;
	Keys mKeyboardInput;

	// Animations
	Animation * mpSmurfWalkAnimation;
	Animation * mpDeanSmurfWalkAnimation;

	// Units
	vector<Unit> mAllUnits;

	// Systems
	System * mpCurrentSystem;

	// Sprties
	Sprite mBackgroundImage;
	Sprite * mpDeanSmurfSprites;
	Sprite * mpForest;
	Sprite * mpSmurfSprites;

	// Graphics Buffers
	GraphicsBuffer * mpForestImage;
	GraphicsBuffer * mpDeanSpriteSheet;
	GraphicsBuffer * mpSmurfSpriteSheet;

	//Manager for Graphics Buffers
	GraphicsBufferManager * mpGraphicsBufferManagement;
	
	//Manager for Units
	UnitManager * mpUnitManagement;

	// Booleans
	bool mIsDisplaying;
};
#endif // !GAME_H

