/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/// <summary>
///		Manages all the units.
/// </summary>
/// <seealso cref="Trackable" />
class UnitManager :
	public Trackable
{
public:
	// Constructor.
	UnitManager();

	// Destructor.
	~UnitManager();

	// Clean up the manager.
	void cleanUp();

	// Add a new unit to the list.
	void addUnit(Unit* _pUnit);

	// Get the last unit.
	Unit* getUnit();

	// Get the unit at position.
	Unit* getUnit(int _position);

	// Get the last player unit.
	Player* getPlayer();

	// Get the player at the given position.
	Player* getPlayer(int _position);

	// Draw each unit to the screen.
	void draw(GraphicsSystem* _pGraphicsSystem);

	// Toggle the animate setting for each unit on/off.
	void toggleAnimation();

	// Update each unit.
	void update(double _deltaTime, LevelManager* _pLevelManager);

	// Clear all the units.
	void clear();

	// Set the direction of the player head.
	void setDirection(int _direction);

	// Update the total player segment count.
	void updatePlayerSize();

	// Get the total player segment count.
	int getPlayerSize();

private:
	// List of created units.
	std::vector<Unit*> mvUnits;

	// Check for collisions with each unit.
	void checkForCollisions();

	// Remove the food spawn from the vector.
	void removeFood();

	void removeCollectable(int _positionX, int _positionY);

	int mPlayerSize = 0;
};