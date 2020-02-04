#ifndef GAME_H
#define GAME_H

// Standard Library includes
#include <vector>
#include <fstream>

// Graphics Library includes
#include <System.h>
#include <InputSystem.h>
#include <EventListener.h>
#include <EventSystem.h>

// Local Project includes
#include "GraphicsBufferManager.h"
#include "UnitManager.h"
#include "InputTranslator.h"
#include "TextManager.h"
#include "FileReader.h"

// Game Performance-related constant variables
const double MAX_TIME_BETWEEN_FRAMES = 16.7;
const int FRAMES_PER_SECOND_DIVISOR = 1000;

// Asset-related constant variables
const string TEXT_FILE_PATH = "..\\..\\lin.steele\\final\\ModFile.txt";
const string UI_TEXT_FILE_PATH = "..\\..\\lin.steele\\final\\ModUIFile.txt";
const string ASSET_PATH_TWO = "..\\..\\lin.steele\\Assets\\";
const string NAME_OF_SCORE_TEXT = "Score Label";
const string NAME_OF_SCORE_AMOUNT_TEXT = "Score Amount";
const string NAME_OF_BACKGROUND_BUFFER = "Background";
const string NAME_OF_PLAYER = "Player";
const string NAME_OF_PLAYER_WALKING_LEFT = "Player Walking Left";
const string NAME_OF_PLAYER_JUMP = "Player Jump";
const string NAME_OF_PLAYER_JUMP_LEFT = "Player Jump Left";
const string NAME_OF_DEFAULT_BLOCK = "Default Block";
const string NAME_OF_BRICK_BLOCK = "Brick Block";
const string NAME_OF_QUESTION_BLOCK = "Question Block";
const string NAME_OF_EMPTY_QUESTION_BLOCK = "Empty Question Block";
const string NAME_OF_BIG_HILL = "Big Hill";
const string NAME_OF_CLOUD = "Cloud";
const string NAME_OF_GOOMBA = "Goomba";
const int BLOCKS_PER_FLOOR = 30;
const double GRAVITY_SCALE = 0.25;
const double JUMP_FORCE = 10.0;
const double WALK_SPEED = 5.0;
const double GOOMBA_WALK_SPEED = 1.0;


// Class Prototypes
class Animation;
class Unit;


class Game : public EventListener
{
public:

	// Friends
	friend class FileReader;

	// Initializers
	void init();
	void initializeSystems();
	static void initStaticInstance();

	// Cleanups
	void cleanup();
	static void destroyStaticInstance();

	// Mutators
	void addBackgroundImage(GraphicsBuffer * newBackground);
	void doLoop();
	void flipDisplay();
	void render();
	void handleEvent(const Event& theEvent);
	void changeFPS(double newFPS);
	void createBlocks(int amountOfBlocks);
	void createGoombas(int amountOfGoombas);

	// Acessors
	static Game* getStaticInstance();
	System * getCurrentSystem();
	UnitManager * getUnitManager();
	TextManager* getTextManager();
	Vector2 getDisplayDimensions();
	Vector2 getPlayerBounds();
	bool getStateOfGame();
	Color getUIColor();

private:

	// Constructors
	Game(EventSystem* pEventSystem);

	// Destructors
	~Game();

	// Static instances
	static Game* mpGameObject;

	// Graphics Buffers Managers
	GraphicsBufferManager mBufferManager;
	UnitManager * mUnitManager;

	// Systems
	System * mCurrentSystem;

	// Input Systems
	InputSystem * mCurrentInputSystem;

	// Input Translators
	InputTranslator * mTranslator;

	// Graphics Buffers
	GraphicsBuffer * mBackgroundImage;

	// Fonts
	Font* mUIFont;

	//Colors
	Color* mUIFontColor;

	// Text Managers
	TextManager * mTextManager;

	// Vector2's
	Vector2 mDisplayDimensions;
	Vector2 mPlayerDimensions;
	Vector2 mDefaultBlockDimensions;
	Vector2 mBrickBlockDimensions;
	Vector2 mQuestionBlockDimensions;
	Vector2 mQuestionBlockEmptyDimensions;
	Vector2 mGoombaDimensions;

	// Animations
	Animation * mPlayerAnimation;
	Animation * mPlayerWalkingAnimationLeft;
	Animation * mBigHillAnimation;
	Animation * mCloudAnimation;
	Animation * mPlayerJumpAnimation;
	Animation * mPlayerJumpLeftAnimation;
	Animation * mDefaultBlockAnimation;
	Animation * mBrickBlockAnimation;
	Animation * mQuestionBlockAnimation;
	Animation * mQuestionBlockEmptyAnimation;
	Animation * mGoombaAnimation;

	// Booleans
	bool mIsDisplaying;
	bool mInApplication;
	bool mInGame;

	// Integers
	int mFramesPerSecond;

	// Doubles
	double mBackgroundScalingValue;

	// Strings

	// Filereaders
	FileReader mReader;

};

#endif // !GAME_H