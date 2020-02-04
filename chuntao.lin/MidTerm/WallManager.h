#ifndef WALL_MANAGER_H
#define WALL_MANAGER_H

// Local Includes
#include "Wall.h"
#include <time.h>
#include "GraphicsBuffer.h"
#include "LevelManager.h"

class WallManager : public Trackable
{
public:

	// Constructors
	WallManager();

	// Destuctors
	~WallManager();

	// Acessors
	Wall getWall(int index);
	Vector2 getWallPos(int index);
	int getSize();
	
	// Initializers
	void spawnWalls(int numWallsWanted,Animation* newAnim);
	void setWallPos();
	void setWallPos(LevelManager* levelManage);

	// Mutators
	void createWall(Vector2 newPos);
	void removeAndDestroyAllWalls();
	void moveWall(int index);
	void addAnimation(int index, Animation & newAnim);
	void swapAnimations(int index);

	// Game Loop Functions
	void update(double timeBetweenFrames);
	
	// Game Loop Functions
	void draw();

private:

	// Vectors
	vector<Wall*> mWalls;

	Vector2 mWallPos;
	double mTimeElapsed = 0;
	double mTargetTime = 60;
	int mCurrentIndex = 0;

};
#endif

