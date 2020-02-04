#ifndef PROP_H
#define PROP_H

#include "Unit.h"

class Prop
{
public:

	// Constructors
	Prop();
	Prop(Vector2 newPos, Animation * newAnim);

	// Destructors
	~Prop();

	// Mutators
	void draw();

private:

	Animation * mCurrentAnimation;
	Vector2 mLocation;

};

#endif // !PROP_H

