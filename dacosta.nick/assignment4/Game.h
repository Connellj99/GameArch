/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/// <summary>
///		A game instance.
/// </summary>
/// <seealso cref="Trackable" />
class Game :
	public Trackable
{
public:
	// Get the instance.
	static Game* getInstance();

	// Initialize the instance.
	static void initializeInstance();

	// Clean up the instance.
	static void cleanUpInstance();

	// Initialize the necessary components.
	void initialize(int _displayWidth, int _displayHeight);

	// Clean up all the components.
	void cleanUp();

	// The main game loop.
	void loop(double _framesPerSecond);

	// Render all the graphics.
	void render(double _deltaTime);

	// Change the game state to end.
	void end();

private:
	// Constructor.
	Game();

	// Destructor.
	~Game();

	// A static instance.
	static Game* mpsInstance;

	// Separate each sprite from its buffer.
	void createSpriteList(GraphicsBuffer* _spriteSheet, Sprite* _pSpriteList, int _rowCount, int _columnCount);

	// Check for keyboard input.
	void checkKeyState();

	// Check for mouse input.
	void checkMouseState();

	// System object.
	System* mpSystem = nullptr;

	// Graphics buffer manager.
	GraphicsBufferManager* mpGraphicsBufferManager;

	// Unit manager.
	UnitManager* mpUnitManager = nullptr;

	// Looping state.
	bool mRunGame = true;

	// List of key checks.
	bool mKeyCheck[KEY_MAX] = { false };

	// List of mouse checks.
	bool mMouseCheck[MOUSE_MAX] = { false };

	// Invalidate copy constructor.
	Game(Game& _game) = delete;

	// Invalidate assignment operator.
	void operator=(const Game& _game);
};