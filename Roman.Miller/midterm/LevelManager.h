#pragma once
#include "Trackable.h"
#include "EventSystem.h"
using namespace std;


class LevelManager: public Trackable
{
public:
	LevelManager();
	~LevelManager();

	void setLevelPointValues(int o, int t, int th, int food);
	void checkPoints();

	int getLevel() { return mLevel; };
	int getCurrentPoints() { return mCurrentPoints; };

	void foodColleted() { mCurrentPoints += mfoodPoints; checkPoints(); };

private:
	int mLevel;
	int mCurrentPoints;

	int mFirstPoints;
	int mSecondPoints;
	int mThirdpoints;
	int mfoodPoints;
};