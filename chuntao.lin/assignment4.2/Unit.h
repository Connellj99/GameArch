#ifndef UNIT_H
#define UNIT_H

// Standard Library includes
#include <vector>

// Project-local includes
#include "Animation.h"
#include "Game.h"
#include "UnitManager.h"

const double DEFAULT_SCALING_VALUE = 1.0;

class UnitManager;

class Unit : public Trackable
{

public:

	// Constructors
	Unit();
	Unit( Vector2 newPos );

	// Destructors
	~Unit();

	// Updates
	void update( double newTimeBetweenFrames );
	void moveToMousePosition( Vector2 newMousePos );

	// Accessors
	bool isVisible();
	void setAnimation( Animation * newAnimation );
	void swapAnimation();
	Animation * getCurrentAnimation();

	void changeAnimationSpeeds( double speedsToBeChanged );//used to change speed of animations
	void toggleAnimationSpeeds();//used to turn animations on and off

	// Mutators
	void draw();

	Vector2 returnLocation();

	void cleanUnitAndSprites();//used to clear unit and deallocate the sprite vectors
	void cleanUnit();//clean just the unit and the animations
	
private:

	// Animations
	vector<Animation*> mpCurrentAnimations;
	
	// Ints
	int mCurrentAnimationIndex;

	// Vector 2s
	Vector2 mCurrentLocation;

};

#endif // !UNIT_H

