/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/// <summary>
///		A game instance.
/// </summary>
/// <seealso cref="Trackable" />
class Game :
	public EventListener
{
public:
	// Get the instance.
	static Game* getInstance();

	// Initialize the instance.
	static void initializeInstance();

	// Clean up the instance.
	static void cleanUpInstance();

	// Initialize the necessary components.
	void initialize(int _gridWidth, int _gridHeight, int _cellWidth, int _cellHeight);

	// Clean up all the components.
	void cleanUp();

	// The main game loop.
	void loop(double _framesPerSecond);

	// Render all the graphics.
	void render(double _deltaTime);

	// Change the game state to end.
	void end();

	GraphicsBufferManager* getGraphicsBufferManager();

	UnitManager* getUnitManager();
	
private:
	// Constructor.
	Game();

	// Destructor.
	~Game();

	// A static instance.
	static Game* smpInstance;

	InputTranslator* mpInputTranslator;

	void handleEvent(const Event& _theEvent);

	void createUnit(int _positionX, int _positionY);

	void createLevel(LevelKey _key, std::vector<int> _map, int _rows, int _columns, int _playerStartLength, int _playerX, int _playerY, double _playerSpeed, int _playerEndLength, int _foodPoints, int _powerUpFrequency);

	void createPlayerHead(int _positionX, int _positionY);

	void addPlayerUnit();

	void removePlayer(int _positionX, int _positionY);

	void toggleAnimation();

	void toggleSprite();

	void changePlayerDirection(int _direction);

	std::string mAssetPath = "";

	std::string mSpritePath = "";

	int mCellWidth = 32;

	int mCellHeight = 32;

	int mGridWidth = 30;

	int mGridHeight = 20;

	void spawnFood();

	void spawnCollectable();

	void switchLevel();

	void addLevelUnits();

	void createPlayer(int _segmentCount, int _spawnX, int _spawnY);

	// System object.
	System* mpSystem = nullptr;

	// Graphics buffer manager.
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;

	// Unit manager.
	UnitManager* mpUnitManager = nullptr;

	// Level manager.
	LevelManager* mpLevelManager = nullptr;

	// Looping state.
	bool mRunGame = true;

	// List of key checks.
	bool mKeyCheck[KEY_MAX] = { false };

	// List of mouse checks.
	bool mMouseCheck[MOUSE_MAX] = { false };

	void startGame();

	void restartGame();

	void gameOver();

	int mScore = 0;

	std::string mSnakeSpriteName = "";

	std::string mWallSpriteName = "";

	std::string mFoodSpriteName = "";

	std::string mBlackBufferName = "";

	std::string mSpeedUpCollectableName = "";

	std::string mSlowDownCollectableName = "";

	std::string mPointsCollectableName = "";

	//void loadConfig();

	//void loadLuaFiles();
};

// Separate each sprite from its buffer.
void createSpriteList(GraphicsBuffer* _spriteSheet, Sprite* _pSpriteList, int _rowCount, int _columnCount);