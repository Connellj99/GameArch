#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "UnitManager.h"
#include <Trackable.h>

class Level :public Trackable
{
private:
	vector<int*> mWallLocations;
	int mPlayerSpeed;
	int mPlayerStartingSegments;
	int mMaxSegmentLength;
	int mFoodPoints;
	int mBonusScore;

	double mAppleFrequency;
	double mSpeedUpFrequency;
	double mSlowDownFrequency;
	double mBonusFrequency;

	string mLevelTitle;

public:
	Level(int newPlayerSpeed, int newStartingPlayerSegments, int newMaxSegmentLength, int newFoodPoints, int bonusScore, string title);
	void addWallLocation(int* wallLocation);
	vector<int*> getWallLocations() { return mWallLocations; }

	void setAppleFrequency(double frequency);
	void setSpeedUpFrequency(double frequency);
	void setSlowDownFrequency(double frequency);
	void setBonusFrequency(double frequency);

	int getPlayerSpeed() { return mPlayerSpeed; }
	int getPlayerStartingSegments() { return mPlayerStartingSegments; }
	int getMaxSegmentLength() { return mMaxSegmentLength; }
	int getFoodPoints() { return mFoodPoints; }
	int getBonusScore() { return mBonusScore; }
	double getAppleFrequency() { return mAppleFrequency; }
	double getSpeedUpFrequency() { return mSpeedUpFrequency; }
	double getSlowDownFrequency() { return mSlowDownFrequency; }
	double getBonusFrequency() { return mBonusFrequency; }
	string getLevelTitle() { return mLevelTitle; }
};

#endif