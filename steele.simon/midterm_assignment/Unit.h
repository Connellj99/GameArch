#ifndef UNIT_H
#define UNIT_H

// Standard Library includes
#include <vector>

// Project-local includes
#include "Animation.h"

const int DEFAULT_SCALING_VALUE = 1;

enum UnitTypes
{
	PLAYER,
	BULLET,
	MUSHROOM,
	CENTIPEDE_SEGMENT,
	NONE
};

class Unit : public Trackable
{
public:

	// Friends
	friend class UnitManager;
	friend class Player;
	friend class Bullet;
	friend class Mushroom;
	friend class CentipedeSegment;

	// Destructors
	~Unit();

	// Updates
	virtual void update( double newTimeBetweenFrames );
	void moveToMousePosition( Vector2 newMousePos );
	void moveToPosition(Vector2 newPos);

	// Accessors
	bool isVisible();
	Vector2 getLocation();
	UnitTypes getCurrentUnitType();
	Animation * getCurrentAnimation();

	// Mutators
	void draw();
	void switchStateOfAnimation();
	void destroyThisGameObject(UnitManager * manager);
	void changeAnimationSpeeds(double speedsToBeChanged);
	void setAnimation(Animation & newAnimation);
	void swapAnimation();

private:

	// UnitTypes
	UnitTypes mUnitType;

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

