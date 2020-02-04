#ifndef UNIT_H
#define UNIT_H

#include "Trackable.h"
#include "Vector2D.h"
#include "Animation.h"
#include <map>

typedef std::string AnimKey;

class Unit : public Trackable
{
public:
	void update(float curTime);
	void draw() const;

	void setAnimation(const AnimKey& key) { mpCurAnimation = &mAnimations[key]; }
	void setLocation(const Vector2D& location) { mLocation = location; }
	Vector2D getLocation() const { return mLocation; }
	void setScale(const Vector2D& scale) { mScale = scale; }
	// whether or not unit intersects the location
	bool intersects(const Vector2D& loc) const;
	// current dimensions of the unit (current sprite * scale)
	Vector2D getDimensions() const;
	void toggleAnimation() { pauseAnim = !pauseAnim; }
private:
	Unit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale);
	~Unit();

	Unit(const Unit&) = delete;
	void operator=(const Unit&) = delete;

	Vector2D mLocation;
	Animation* mpCurAnimation;
	std::map<AnimKey, Animation> mAnimations;
	Vector2D mScale;
	bool pauseAnim = false;

	friend class UnitManager;
};
#endif