#ifndef POWER_UP_MANAGER_H
#define POWER_UP_MANAGER_H

#include "Unit.h"
#include <time.h>

class PowerUpManager : public Trackable
{
public:

	// Constructors
	PowerUpManager();
	PowerUpManager(double spawnTime);

	// Destuctors
	~PowerUpManager();

	// Acessors
	Unit getUnit(int index);
	string getUnitType(int index);
	int getSize();
	Vector2 getPos(int index);
	bool getSpawnStatus() { return mCanSpawn; }
	double getSpawnFreq() { return mTargetTime; }

	// Initializers
	void spawnPowerUps(string type,Animation* animationOne, Animation* animationTwo);
	void spawnPowerUps(string type, Animation* animationOne);
	int randomPowerUpSpawnNumber();
	void setPowerUpPos();

	// Mutators
	void createPowerUp(Vector2 newPos);
	void createPowerUp(Vector2 newPos,string type);
	void createPowerUp(Vector2 newPos, string type,bool moved);
	void destroyPowerUp(int index);
	void removeAndDestroyAllPowerUps();
	void addAnimation(int index, Animation & newAnim);
	void swapAnimations(int index);
	void movePowerUp();
	void movePowerUp(int index);
	void setSpawnStatus(bool status) { mCanSpawn = status; };
	void setSpawnFreq(double freq) { mTargetTime = freq; }

	// Game Loop Functions
	void updatePowerUps(double timeBetweenFrames);
	void updateSpawn(float timeBetweenFrames);
	void drawPowerUps();
	
private:

	// Vectors
	vector<Unit*> mPowerUps;

	Vector2 mPowerUpPos;

	bool mCanSpawn = false;

	double mPowerTimeElapsed = 0;
	double mPowerTargetTime = 60;
	int mCurrentCount = 0;

	double mTimeElapsed = 0;
	double mTargetTime = 60;
	int mCurrentIndex = 0;
};
#endif