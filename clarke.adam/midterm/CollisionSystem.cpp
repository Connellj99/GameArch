#include "CollisionSystem.h"
#include "BoxCollision2D.h"
#include "BoxCollider2D.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::addCollider(BoxCollider2D* collider)
{
	mColliders.push_back(collider);
}

std::vector<BoxCollision2D> CollisionSystem::checkCollisions(BoxCollider2D* withCollider)
{
	std::vector<BoxCollision2D> collisions;
	if (!withCollider->getEnabled())
	{
		return collisions;
	}

	// TODO: fix this methdod's variable names, they all suck
	const auto withLoc = withCollider->getLoc();
	const auto withDim = withCollider->getDim();
	for (const auto& collider : mColliders)
	{
		const auto loc = collider->getLoc();
		const auto dim = collider->getDim();
		if (collider && collider->getEnabled() && collider != withCollider
			&& loc.getX() < withLoc.getX() + withDim.getX()
			&& loc.getX() + dim.getX() > withLoc.getX()
			&& loc.getY() < withLoc.getY() + withDim.getY()
			&& loc.getY() + dim.getY() > withLoc.getY())
		{
			collisions.push_back(BoxCollision2D(collider));
		}
	}
	return collisions;
}
