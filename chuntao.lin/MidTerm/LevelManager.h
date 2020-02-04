#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "Trackable.h"
#include <vector>

#include "Vector2Data.h"

class LevelManager : public Trackable
{
public:
	friend class WallManager;

	LevelManager(int maxLevels);
	~LevelManager();

	//Cleanup
	void cleanUp();

	//Accessors
	int getCurrentLevel() { return mCurrentLevel; }
	int getCurrentLevelLength() { return mLevelLengths[mCurrentLevel-1]; }
	bool getLevelStatus() { return mLevelsDone; }

	//Mutators 
	void nextLevel() { mCurrentLevel += 1; }
	void setLevelSnakeRequirements(int requiredNumber);
	void setLevelWallRequirements(Vector2 pos);

	void checkLevels();

private:

	//Levels
	int mCurrentLevel;
	int mTotalLevels;
	bool mLevelsDone;

	//Length requirements for each lvl
	std::vector<int>mLevelLengths;
	int mLevelLengthRequirement;

	//WallPositions for each wall in a level
	/*std::vector<std::vector<Vector2> > mvWallPos;*/
	std::vector<Vector2> mvWallPos;
	//std::vector<int>mWallPos;
	//Vector2 mWallPos;
};

#endif