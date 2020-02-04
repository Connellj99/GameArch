#ifndef CENTIPEDESEGMENT_H
#define CENTIPEDESEGMENT_H

// Local includes
#include "Unit.h"

// Constants
const double MAX_AMOUNT_OF_TIME = 80.0;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class CentipedeSegment : public Unit
{
public:
	// Constructors
	CentipedeSegment();
	CentipedeSegment(Vector2 newPos);

	// Destructors
	~CentipedeSegment();

	// Update functions
	void update(double newTimeBetweenFrames);
	void updateAnimations();
	void checkForCollision();

	// Mutators
	void changeDirection(Direction newDirection);
	void addNextSegment(CentipedeSegment * newSegment);
	void addLastSegment(CentipedeSegment * newSegment);
	void calculateSegmentDirection(Direction newDirection, Direction newVerticalDirection);
	void moveCentipedeSegment();
	void pivotCentipedeBasedOnPosition();
	void pivotCentipedeBasedOnUnitCollisions();
	bool checkForAnyMushroomCollisions( Vector2 posToBeChecked);

	// Accessors
	CentipedeSegment * getNextSegment();
	CentipedeSegment * getLastSegment();

private:

	// Units
	CentipedeSegment * mNext;
	CentipedeSegment * mLast;

	// Doubles
	double mRemainingTime;
	double mTimeElapsed;

	// Directions
	Direction mCurrentDirection;
	Direction mLastHorizontalDirection;
	Direction mVerticalDirection;

	// Booleans
	bool mHasBeenMovedByMushroom;

};

#endif // !CENTIPEDESEGMENT_H

