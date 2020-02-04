#include "Level.h"

Level::Level(int newPlayerSpeed, int newStartingPlayerSegments, int newMaxSegmentLength, int newFoodPoints, int bonusScore, string title)
	: mPlayerSpeed(newPlayerSpeed), mPlayerStartingSegments(newStartingPlayerSegments), mMaxSegmentLength(newMaxSegmentLength), mFoodPoints(newFoodPoints), mBonusScore(bonusScore), mLevelTitle(title)
{
	mAppleFrequency = 10;
	mSpeedUpFrequency = 35;
	mSlowDownFrequency = 35;
	mBonusFrequency = 70;
}

void Level::addWallLocation(int* wallLocation)
{
	mWallLocations.push_back(wallLocation);
}

void Level::setAppleFrequency(double frequency)
{
	mAppleFrequency = frequency;
}

void Level::setSpeedUpFrequency(double frequency)
{
	mSpeedUpFrequency = frequency;
}

void Level::setSlowDownFrequency(double frequency)
{
	mSpeedUpFrequency = frequency;
}

void Level::setBonusFrequency(double frequency)
{
	mBonusFrequency = frequency;
}