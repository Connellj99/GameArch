#pragma once

class PlayerManager :
	public UnitManager
{
public:
	PlayerManager();

	// Destructor.
	virtual ~PlayerManager();

	// Clean up the manager.
	virtual void cleanUp();

	// Add a new unit to the list.
	virtual void addUnit(Player* _pPlayer);

	// Remove a unit
	void deleteUnit(int _collisionX, int _collisionY);

	// Get the last unit.
	virtual Player* getUnit();

	// Get the unit at position.
	virtual Player* getUnit(int _position);

	// Draw each unit to the screen.
	virtual void draw(GraphicsSystem* _pGraphicsSystem);

	// Move all the units in the direction of the new position.
	void setDirection(int _direction);

	// Update each unit's animation.
	virtual void update(double _deltaTime);

	// Clear all the units.
	virtual void clear();

private:
	std::vector<Player*> mvPlayer;
};

