#ifndef BOX_COLLIDER2D_H
#define BOX_COLLIDER2D_H

#include "Trackable.h"
#include "Vector2D.h"
#include "CollisionSystem.h"
#include "BoxCollision2D.h"

typedef std::string Tag;

class BoxCollider2D : public Trackable
{
public:
	BoxCollider2D(const Tag& tag, const Vector2D& loc, const Vector2D& dim,
		CollisionSystem* collisionMap)
		: mTag(tag), mLoc(loc), mDim(dim), pCollisionMap(collisionMap)
	{
		mIsEnabled = true;
		pCollisionMap->addCollider(this);
	}
	virtual ~BoxCollider2D() {}

	virtual void physicsUpdate(float curTime)
	{
		for (const auto& collision : pCollisionMap->checkCollisions(this))
		{
			onCollision(collision);
		}
	}

	std::string getTag() const { return mTag; }
	Vector2D getLoc() const { return mLoc; }
	Vector2D getDim() const { return mDim; }
	bool getEnabled() const { return mIsEnabled; }
protected:
	virtual void onCollision(const BoxCollision2D& collision) = 0;

	void setTag(const std::string& tag) { mTag = tag; }
	void setLoc(const Vector2D& loc) { mLoc = loc; }
	void setDim(const Vector2D& dim) { mDim = dim; }
	void setEnabled(bool enabled) { mIsEnabled = enabled; }
private:
	Tag mTag;
	Vector2D mLoc;
	Vector2D mDim;
	bool mIsEnabled;
	CollisionSystem* pCollisionMap;
};
#endif
