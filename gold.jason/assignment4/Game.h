/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Game;

// Declare a global game object.
extern Game* gpGame;

/// <summary>
///		A game instance.
/// </summary>
/// <seealso cref="Trackable" />
class Game :
	public Trackable
{
public:
	// Constructor.
	Game();

	// Destructor.
	~Game();

	// Initialize the necessary components.
	void initialize(int _displayWidth, int _displayHeight);

	// Clean up all the components.
	void cleanUp();

	// The main game loop.
	void loop(double _framesPerSecond);

	//draw everything to screen
	void drawStuff();

	// Change the game state to end.
	void end();

private:
	// Separate each sprite from its buffer.
	void createSpriteList(GraphicsBuffer* _spriteSheet, Sprite* _pSpriteList, int _rowCount, int _columnCount);

	// Check for keyboard input.
	void checkKeyState();

	// Check for mouse input.
	void checkMouseState(GraphicsSystem* mSys);

	// System object.
	System* mpSystem = nullptr;

	// Woods buffer.
	GraphicsBuffer* mpWoodsBuffer = nullptr;

	// Smurf buffer.
	GraphicsBuffer* mpSmurfBuffer = nullptr;

	// Dean smurf buffer.
	GraphicsBuffer* mpDeanBuffer = nullptr;

	// Smurf sprites.
	Sprite* mpSmurfSprites = nullptr;

	// Dean sprites.
	Sprite* mpDeanSprites = nullptr;

	// Unit Manager
	Unit* mpUnit = nullptr;

	// An animation clip.
	Animation* mpAnimation = nullptr;

	// Looping state.
	bool mRunGame = true;

	// Enter key check.
	bool mPressedEnter = false;

	// S key check.
	bool mPressedS = false;

	// F key check.
	bool mPressedF = false;
};