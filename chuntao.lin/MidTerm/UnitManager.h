#ifndef UNITMANAGER_H
#define UNITMANAGER_H

// Local Includes
#include "Unit.h"

#include "WallManager.h"
#include "PowerUpManager.h"

// Constant Vector2's
const Vector2 CLICK_DIMENSIONS = Vector2( 35, 35 );

class UnitManager: public Trackable
{
public:

	// Constructors
	UnitManager();

	// Destuctors
	~UnitManager();

	// Acessors
	Unit getUnit( int index );
	Vector2 getUnitPos(int index);
	int getSize();

	bool getFruitStatus() { return mEatFruit; }
	bool getCrashStatus() {return mCrashedWall;}
	bool getPowerUpStatus() { return mEatPowerUp; }
	int getPowerUpTypeStatus();

	// Initializers
	void spawnSnake(int numUnitsWanted, Animation* animationOne, Animation* animationTwo);
	void spawnSnake(int numUnitsWanted, Animation* animationOne);
	void resetEating();//just resets the bool that says yes the snake ate a fruit

	// Mutators
	void createUnit(Vector2 newPos);
	void increaseLength(Vector2 newPos, Animation* animationOne, Animation* animationTwo);//if user wants two animations to switch between
	void increaseLength(Vector2 newPos, Animation* animationOne);//for my use, only one animation spritesheet
	void destroyUnit(int index);
	void removeAndDestroyAllUnits();
	void addAnimation( int index, Animation & newAnim );
	void swapAnimations( int index );
	void playOrStopUnitAnimations();
	void deleteUnitFromGivenPoint( Vector2 newPos );
	void setFruitStatus(bool newFruitStatus);
	void setPowerUpStatus(bool newPowerUpStatus);
	void setCrashStatus(bool newWallStatus);

	// Game Loop Functions
	void update( double timeBetweenFrames );
	void draw();
	void checkPositionFromBorderWalls();//checks position of the head of the snake from the walls
	void checkPositionFromBody();//checks position of the head of the snake to rest of the body
	void checkPositionFromFood(Vector2 position);//checks position of the head of the snake from any fruit
	void checkPositionFromWalls(WallManager* wallManage);//checks position of the head of the snake from any fruit
	void checkPositionFromPowerUps(PowerUpManager* powerUpManage);//check the position of the head from any powerup

	//Movement
	void moveUnitsLeft(int speed,double framesPassed);
	void moveUnitsRight(int speed, double framesPassed);
	void moveUnitsUp(int speed, double framesPassed);
	void moveUnitsDown(int speed, double framesPassed);

private:

	// Vectors
	vector<Unit*> mUnits;

	double mTimeElapsed = 0;
	double mTargetTime = 60;
	int mCurrentIndex = 0;

	// Booleans
	bool mEatFruit = false;//see if the player has eaten a grow fruit
	bool mCrashedWall = false;//see if the player has hit a spawned wall

	bool mEatPowerUp = false;//see if the player has eaten a power up
	bool mBonusPt = false;//see if it the player eats a bonus point power up
	bool mSlowDown = false;//see if it the player eats a slow power up
	bool mSpeedUp = false;//see if it the player eats a fast power up
};
#endif // !UNITMANAGER_H

