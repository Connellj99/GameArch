#ifndef UNIT_H
#define UNIT_H

#include "Animation.h"
#include <map>
#include "BoxCollider2D.h"

typedef std::string AnimKey;

class Unit : public BoxCollider2D
{
public:
	virtual void update(float curTime);
	virtual void draw() const;

	void setAnimation(const AnimKey& key);
	void addAnimation(const AnimKey& key, Animation animation);
	void setLocation(const Vector2D& location) { mLocation = location; BoxCollider2D::setLoc(mLocation); }
	Vector2D getLocation() const { return mLocation; }
	void setScale(const Vector2D& scale) { mScale = scale; calcDimensions(); }
	Vector2D getScale() const { return mScale; }
	// whether or not unit intersects the location
	bool intersects(const Vector2D& loc) const;
	// current dimensions of the unit (current sprite * scale)
	Vector2D getDimensions() const { return mDimensions; }
	void toggleAnimation() { mPauseAnim = !mPauseAnim; }
	void setFlipHorizontal(bool doFlip) { mFlipHorizontal = doFlip; }
	void flipSpriteHorizontal() { mFlipHorizontal = !mFlipHorizontal; }
	bool getActive() const { return mIsActive; }
	void setActive(bool active) { mIsActive = active; BoxCollider2D::setEnabled(active); }
protected:
	Unit(CollisionSystem* collisionMap, const std::string& tag);
	Unit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale,
		CollisionSystem* collisionMap, const std::string& tag);
	~Unit();

	void onCollision(const BoxCollision2D& collision) override = 0;
	Animation* getCurAnimation() const { return mpCurAnimation; }
private:
	Unit(const Unit&) = delete;
	void operator=(const Unit&) = delete;

	Vector2D mLocation = Vector2D(0, 0);
	Animation* mpCurAnimation = nullptr;
	std::map<AnimKey, Animation> mAnimations;
	Vector2D mScale = Vector2D(1, 1);
	Vector2D mDimensions = Vector2D(0, 0);
	bool mFlipHorizontal = false;
	bool mPauseAnim = false;
	bool mIsActive = true;

	void calcDimensions();

	friend class UnitManager;
};
#endif