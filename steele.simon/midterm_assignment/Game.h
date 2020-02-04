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
const string TEXT_FILE_PATH = "..\\..\\steele.simon\\midterm_assignment\\ModFile.txt";
const string ASSET_PATH_TWO = "..\\..\\steele.simon\\Assets\\";
const string NAME_OF_BACKGROUND_BUFFER = "Background";
const string NAME_OF_CENTIPEDE_HEAD_BUFFER = "Centipede Head Sprite Sheet";
const string NAME_OF_CENTIPEDE_SEGMENT_BUFFER = "Centipede Segment Sprite Sheet";
const string NAME_OF_PLAYER = "Player";
const string NAME_OF_BULLET = "Bullet";
const string NAME_OF_FIRST_MUSHROOM = "Mushroom_One";
const string NAME_OF_SECOND_MUSHROOM = "Mushroom_Two";
const string NAME_OF_THIRD_MUSHROOM = "Mushroom_Three";
const string NAME_OF_FOURTH_MUSHROOM = "Mushroom_Four";
const string NAME_OF_INTRO_TEXT = "Intro_Text";
const string NAME_OF_INSTRUCT_TEXT = "Instruction_Text";
const string NAME_OF_END_TEXT = "End_Text";
const string NAME_OF_SCORE_TEXT = "Score_Text";
const string NAME_OF_LIVES_REMAINING_DISPLAY_TEXT = "Lives_Remaining_Display";
const string NAME_OF_LIVES_REMAINING_TEXT = "Lives_Remaining";
const string NAME_OF_FPS_TEXT = "FPS";

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
	void shootBullet();
	void spawnMushrooms();
	void createMushroom( Vector2 newPos );
	void endLife();
	void endGame();
	void restartGame();
	void endApplication();
	void addToScore( int scoreToBeAdded );
	void startGame();
	void deductNumOfSegments();
	void changeFPS(double newFPS);

	// Acessors
	static Game* getStaticInstance();
	System * getCurrentSystem();
	UnitManager * getUnitManager();
	double getCentipedeSpeed();
	Vector2 getBoundsOfPlayer();
	int getInitialHealthOfMushroom();
	int getScoringValueForCentipedeSegment();
	int getBulletSpeed();
	Vector2 getDisplayDimensions();
	Vector2 getMushroomDimensions();
	Vector2 getCentipedeDimensions();
	bool getStateOfGame();

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

	// Animations
	Animation * mCentipedeHeadAnimation;
	Animation * mCentipedeSegmentAnimation;
	Animation * mPlayerAnimation;
	Animation * mMushroomOneAnimation;
	Animation * mMushroomTwoAnimation;
	Animation * mMushroomThreeAnimation;
	Animation * mMushroomFourAnimation;
	Animation * mBulletAnimation;

	// Systems
	System * mCurrentSystem;

	// Input Systems
	InputSystem * mCurrentInputSystem;

	// Input Translators
	InputTranslator * mTranslator;

	// Graphics Buffers
	GraphicsBuffer * mBackgroundImage;

	// Fonts
	Font * mGameFont;

	// Text Managers
	TextManager * mTextManager;

	// Vector2's
	Vector2 mPlayerDimensions;
	Vector2 mBulletDimensions;
	Vector2 mMushroomDimensions;
	Vector2 mPlayerBounds;
	Vector2 mInitialCentipedePosition;
	Vector2 mDisplayDimensions;
	Vector2 mCentipedeDimensions;

	// Booleans
	bool mIsDisplaying;
	bool mInApplication;
	bool mInGame;

	// Integers
	int mNumOfSegments;
	int mNumOfSegmentsRemaining;
	int mMushroomsPerLevel;
	int mScore;
	int mNumOfWaves;
	int mPlayerLives;
	int mPlayerInitialLives;
	int mInitialSpeedOfCentipede;
	int mInitialHealthOfAMushroom;
	int mCentipedeScoringValue;
	int mBulletSpeed;
	int mExtraLifeMinimumScore;
	int mNumberOfTimeExtraLifeRewarded;
	int mFramesPerSecond;

	// Doubles
	double mBackgroundScalingValue;

	// Strings
	string mLivesRemainingDisplayTextMessage;
	string mLivesRemainingTextMessage;
	string mFPSTextMessage;
	string mScoreTextMessage;

	// Filereaders
	FileReader mReader;

};

#endif // !GAME_H