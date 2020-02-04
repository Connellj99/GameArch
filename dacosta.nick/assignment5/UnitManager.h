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

	// Remove a unit
	void deleteUnit(int _collisionX, int _collisionY);

	// Get the last unit.
	Unit* getUnit();

	// Draw each unit to the screen.
	void draw(GraphicsSystem* _pGraphicsSystem);

	// Toggle the animate setting for each unit on/off.
	void toggleAnimation();

	// Update each unit's animation.
	void update(double _deltaTime);

	// Clear all the units.
	void clear();

private:
	// List of created units.
	std::vector<Unit*> mvUnits;
};