#pragma once
#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Trackable.h"
#include "Unit.h"
#include <vector>
#include <map>

class Unit;

using namespace std;

class UnitManager :public Trackable
{
private:
	bool mCleanedUp = false;

	Unit* mpPlayer; // Can only have one player.
	Unit* mpBody;
	map<string, Unit*> mUnits;
	vector<Unit*> mAlwaysCreate;
	vector<Unit*> mUnitStorage;
	vector<Unit*> mWallStorage;
	vector<Unit*> mUnitStorageNoClear;
	vector<Unit*> mBodyStorage;
	vector<Unit*> mBoundaries;
	vector<int*> mWallLocations;
	vector<int*> mPastPlayerLocations;
	int mNumPlayerSegments = 0;
	int mLengthOfPlayer = 1;
public:
	UnitManager();
	~UnitManager();
	void addUnit(string unitName, Unit* unit);
	void addAlwaysCreate(string unitName);
	void addAlwaysCreate(Unit* unit);
	void addToStorage(string unitName);
	void addToBodyStorage(Unit* unit);
	void removeFromBodyStorage(Unit* unit);
	void addToStorage(Unit* unit);
	void removeFromStorage(Unit* unit);
	void removePowerupFromStorage(Unit* unitName);
	void instantiateAtMouse(bool mouseDown, int* CurrentMousePos, System* drawingSystem, int offset);
	void addPlayer(string playerName, string bodyName);
	void addPlayer(Unit* player, Unit* body);
	bool playerCollidedWithBody(int offset);
	bool playerCollidedWithPowerup(Unit* unitName, int offset);
	int getLengthOfPlayer();
	int getMaxPlayerLength();
	void addBoundarieBox(string unitName, int minWidth, int maxWidth, int minHeight, int maxHeight, int increments, int offset);
	void addWall(string unitName, int startX, int startY, int endX, int endY, int offset);
	bool playerCollidedWithWall(int offset);
	void addToStorageNoClear(Unit* unitName);
	void addWallAtPosition(string unitName, int xPos, int yPos);
	void increasePlayerLengthBy(int amount);
	void increasePlayerLengthAndResetBody(int amount);
	void addToWallStorage(Unit* unit);
	int placePlayer(int* playerPosition);
	void swapFrozen();
	void removeAtCoords(int* coords);
	void incrementLastSpriteAnimation();
	void deleteUnit(string unitName);
	Unit* getUnit(string unitName);
	void clearBodyStorage();
	void clearWallStorage();
	void clear();
	void update(double elapsedTime);
	void cleanup();
	void draw(System* drawingSystem, float scale, int offset);
};

#endif // !UNITMANAGER_H
