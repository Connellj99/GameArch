#ifndef COLLISION_MAP_H
#define COLLISION_MAP_H

#include "Trackable.h"
#include <vector>

class BoxCollider2D;
class BoxCollision2D;

class CollisionSystem : public Trackable
{
public:
	CollisionSystem();
	~CollisionSystem();

	void addCollider(BoxCollider2D* collider);
	std::vector<BoxCollision2D> checkCollisions(BoxCollider2D* withCollider);
private:
	std::vector<BoxCollider2D*> mColliders;
};
#endif