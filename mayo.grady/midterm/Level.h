#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Midterm
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include <string>
#include <fstream>
#include <vector>
#include "Vector2D.h"

using namespace std;

const int MILLI_SEC = 1000;

class Level : public Trackable
{
private:
	string mFilename;

	//filedata for the level
	string mAssetPath;
	string mFontFilename;
	int mFontSize;
	string mWallFilename;
	string mHeadFilename;
	string mBodyFilename;
	string mBackgroundFilename;
	string mFoodFilename;
	int mFoodRow;
	int mFoodCol;
	string mBonusFilename;
	int mBonusRow;
	int mBonusCol;
	string mFastFilename;
	int mFastRow;
	int mFastCol;
	string mSlowFilename;
	int mSlowRow;
	int mSlowCol;
	int mDispWidth;
	int mDispHeight;
	double mDesiredFPS;
	int mSpriteSize;
	int mNumWalls;
	vector<Vector2D*> mvWallList;
	int mSpeed;
	int mSegments;
	int mTarget;
	int mFoodScore;
	int mPowerFreq;
	int mFastValue;
	int mSlowValue;
	int mBonusValue;

public:
	//constructor & destructor
	Level(string filename);
	~Level();

	//read info from file and populate in member data
	void readFromFile();

	//accessors for member data
	string getAssetPath() { return mAssetPath; };
	string getFontFilename() { return mFontFilename; };
	int getFontSize() { return mFontSize; };
	string getWallFilename() { return mWallFilename; };
	string getHeadFilename() { return mHeadFilename; };
	string getBodyFilename() { return mBodyFilename; };
	string getBackgroundFilename() { return mBackgroundFilename; };
	string getFoodFilename() { return mFoodFilename; };
	int getFoodRow() { return mFoodRow; };
	int getFoodCol() { return mFoodCol; };
	string getBonusFilename() { return mBonusFilename; };
	int getBonusRow() { return mBonusRow; };
	int getBonusCol() { return mBonusCol; };
	string getFastFilename() { return mFastFilename; };
	int getFastRow() { return mFastRow; };
	int getFastCol() { return mFastCol; };
	string getSlowFilename() { return mSlowFilename; };
	int getSlowRow() { return mSlowRow; };
	int getSlowCol() { return mSlowCol; };
	int getDispWidth() { return mDispWidth; };
	int getDispHeight() { return mDispHeight; };
	double getDesiredFPS() { return mDesiredFPS; };
	int getSpriteSize() { return mSpriteSize; };
	int getNumWalls() { return mNumWalls; };
	Vector2D * getWPos(int index) { return mvWallList[index]; };
	int getSpeed() { return mSpeed; };
	int getSegments() { return mSegments; };
	int getTarget() { return mTarget; };
	int getFoodScore() { return mFoodScore; };
	int getPowerFreq() { return mPowerFreq; };
	int getFastValue() { return mFastValue; };
	int getSlowValue() { return mSlowValue; };
	int getBonusValue() { return mBonusValue; };
};