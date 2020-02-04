#pragma once
#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "UnitManager.h"
#include "Level.h"
#include <Trackable.h>

class LevelManager :public Trackable
{
private:
	int mLevelIndex;
	vector<Level*> mLevelList;

	bool isCleared = false;
	
public:
	LevelManager(int levelIndex = 0);
	void addLevel(Level* levelToAdd);
	Level* getLevel(int index);
	Level* getLevelAtCurrentIndex();
	string getCurrentLevelTitle();
	int endLevel();
	void goToLastLevel();
	void goToStartLevel();
	void clear();

	~LevelManager();
};

#endif