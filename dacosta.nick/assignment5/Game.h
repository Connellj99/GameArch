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
	static Game* smpInstance;

	InputTranslator* mpInputTranslator;

	void handleEvent(const Event& _theEvent);

	// Separate each sprite from its buffer.
	void createSpriteList(GraphicsBuffer* _spriteSheet, Sprite* _pSpriteList, int _rowCount, int _columnCount);

	void createUnit(int _positionX, int _positionY);

	void removeUnit(int _positionX, int _positionY);

	void toggleAnimation();

	void toggleSprite();

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
};