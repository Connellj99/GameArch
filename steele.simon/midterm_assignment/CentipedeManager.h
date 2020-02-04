#ifndef CENTIPEDEMANAGER_H
#define CENTIPEDEMANAGER_H

// Local Project includes
#include "Unit.h"
#include "CentipedeSegment.h"

const double DEFAULT_ANIMATION_SPEED = 300.0;

class CentipedeManager
{
public:
	// Constructors
	CentipedeManager();

	// Destructors
	~CentipedeManager();

	// Mutators
	void addSegmentToCentipede(CentipedeSegment* segmentToBeAdded);
	void removeSegmentOfCentipede(CentipedeSegment * unitToBeRemoved);
	void addAnimation(Animation & newAnim);
	void changeHeadAnimation();
	void resetAnimations();

	// Update functions
	void update(double timeBetweenFrames);
	void draw();

private:

	// Centipede Segments
	CentipedeSegment * mHead;

	// Doubles
	double mTimeElapsed;

};

#endif // !CENTIPEDEMANAGER_H


