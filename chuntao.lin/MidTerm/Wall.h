#ifndef WALL_H
#define WALL_H

// Standard Library includes
#include <vector>
#include "Animation.h"

#include "Vector2Data.h"

#include "Trackable.h"

using namespace std;

class Wall : public Trackable
{
public:

	// Friends
	friend class WallManager;

	// Destructors
	~Wall();

	//Updates
	void update(double newTimeBetweenFrames);

	// Accessors
	bool isVisible();
	void setAnimation(Animation & newAnimation);

	Animation * getCurrentAnimation();

	// Mutators
	void draw();
	void swapAnimation();

private:

	// Constructors
	Wall();
	Wall(Vector2 newPos);
	Wall(Vector2 newPosition, Animation * newAnimation);

	// Animations
	vector<Animation*> mCurrentAnimations;

	// Ints
	int mCurrentAnimationIndex;

	// Vector 2s
	Vector2 mWallCurrentLocation;
};
#endif

