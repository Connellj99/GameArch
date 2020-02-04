#pragma once
#include "Unit.h"
#include <vector>

class UnitManager : public Trackable
{
private:
	std::vector<Unit*> mUnitList;

public:
	UnitManager();
	~UnitManager();

	void init();
	void cleanup();

	void addNewUnit(GraphicsBuffer* spriteMap, int rows, int columns);
	void addUnit(Unit* unit);

	Unit* getUnit(int index);

	int getSize();

	void removeUnit(int index);
	void removeAllUnits();
	void removeUnitsAt(float x, float y);

	void removeSpecificUnit(Unit* type);

	void setX(float x, int index);
	void setY(float y, int index);
	float getX(int index);
	float getY(int index);

	void update();
	void draw();

	int findIndex(Unit* unit);
};