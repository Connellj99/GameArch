/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once


/// <summary>
///		Systems manager.
/// </summary>
/// <seealso cref="Trackable" />
class System :
	public Trackable
{
public:
	// Allow the game class to access member items.
	friend class Game;

	// Constructor.
	System();

	// Destructor.
	~System();

	// Initialize all the components required to run the system.
	void initialize(int _displayWidth, int _displayHeight);

	// Clean up all the initialized componenets.
	void cleanUp();

	// Get the Graphics System.
	GraphicsSystem* getGraphicsSystem();

	// Get the input and update the graphics system.
	void update();

private:
	// Graphics system.
	GraphicsSystem* mpGraphicsSystem = nullptr;

	InputSystem* mpInputSystem = nullptr;
};