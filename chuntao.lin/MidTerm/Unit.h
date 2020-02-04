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
	friend class FoodManager;
	friend class PowerUpManager;

	// Destructors
	~Unit();

	// Updates
	void update( double newTimeBetweenFrames );
	void moveToMousePosition( Vector2 newMousePos );

	// Accessors
	bool isVisible();
	void setAnimation( Animation & newAnimation );
	void swapAnimation();
	Vector2 getPos() { return mCurrentLocation; }
	void setNewPos(Vector2 newPos) {mCurrentLocation = newPos;}

	Animation * getCurrentAnimation();
	string getType() { return mType; }
	bool getMoveStatus() { return mHasMoved; }

	void changeAnimationSpeeds( double speedsToBeChanged );

	// Mutators
	void draw();//default draw
	void draw(string typeName);//draw for player
	void switchStateOfAnimation();
	void setMoveStatus(bool status);

private:

	// Constructors
	Unit();
	Unit(Vector2 newPos);
	Unit(Vector2 newPos,string type);
	Unit(Vector2 newPos, string type, bool moved);
	Unit(Vector2 newPosition, Animation * newAnimation);

	// Animations
	vector<Animation*> mCurrentAnimations;

	// Strings
	string mType;

	bool mHasMoved;

	// Ints
	int mCurrentAnimationIndex;

	// Vector 2s
	Vector2 mCurrentLocation;

	// Booleans
	bool isAnimationStopped;

};

#endif // !UNIT_H

