#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "Trackable.h"
#include "Unit.h"

// holds a list of all Units in the game
class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	Unit* createUnit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale);
	// get all units whose sprite intersects atLoc
	std::vector<Unit*> getUnits(const Vector2D& atLoc);
	// returns whether or not deleted unit was most recently added unit
	bool destroyUnit(Unit* unit);
	void toggleAnimations();

	// remove and delete all units
	void clear();
	void update();
	void draw();
private:
	std::vector<Unit*> mUnits;
};
#endif