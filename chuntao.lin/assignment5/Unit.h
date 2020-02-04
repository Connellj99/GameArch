#ifndef UNIT_H
#define UNIT_H

// Standard Library includes
#include <vector>

// Project-local includes
#include "Animation.h"

const double DEFAULT_SCALING_VALUE = 1.0;

class Unit : public Trackable
{
public:

	// Friends
	friend class UnitManager;

	// Destructors
	~Unit();

	// Updates
	void update( double newTimeBetweenFrames );
	void moveToMousePosition( Vector2 newMousePos );

	// Accessors
	bool isVisible();
	void setAnimation( Animation & newAnimation );
	void swapAnimation();

	Animation * getCurrentAnimation();
	void changeAnimationSpeeds( double speedsToBeChanged );

	// Mutators
	void draw();
	void switchStateOfAnimation();

private:

	// Constructors
	Unit();
	Unit(Vector2 newPos);
	Unit(Vector2 newPosition, Animation * newAnimation);

	// Animations
	vector<Animation*> mCurrentAnimations;

	// Ints
	int mCurrentAnimationIndex;

	// Vector 2s
	Vector2 mCurrentLocation;

	// Booleans
	bool isAnimationStopped;

};

#endif // !UNIT_H

