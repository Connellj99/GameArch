#pragma once
#include "Unit.h"
#include<vector>
#include "Trackable.h"

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void addUnit(Unit *unit);
	void addUnit(vector<Unit*> unit);

	void createUnit(Animation ani, Vector2D position, string type);
	void createUnit(vector<Animation> ani, Vector2D position, string type);
	
	void updateUnit();
	void updateUnit(int index);

	Unit* getUnit(int index);
	Unit* getUnit();

	void checkOverlap(Vector2D pos);

	void deleteAllUnits();
	void deleteByPosition(Vector2D pos);
	void deleteByPositionAndType(Vector2D pos, string type);
	void deleteByIndex(int index);
	
	bool containsObjectOfType(string type);

	void draw(int index);
	void draw();

	void pausePlayAllUnits();

private:
	vector<Unit*>mpUnitVec;

};