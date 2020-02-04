#ifndef UNIT_H
#define UNIT_H

#include "Trackable.h"
#include "Vector2D.h"
#include "Animation.h"

class Unit : public Trackable
{
public:
	Unit(Animation* initAnimation, const Vector2D& initLoc, const Vector2D& scale);
	Unit(const Vector2D& initLoc, const Vector2D& scale);
	~Unit();

	void update();
	void draw() const;

	void setAnimation(Animation* animation);
	void setLocation(const Vector2D& location) { mLocation = location; }
	void setScale(const Vector2D& scale) { mScale = scale; }
private:
	Unit(const Unit&);
	void operator=(const Unit&);

	Vector2D mLocation;
	Animation* mpAnimation;
	Vector2D mScale;
};
#endif