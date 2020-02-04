#include "Projectile.h"
#include "System.h"

Projectile::Projectile(Sprite* sprite, int x, int y)
{
	mBullet = *sprite;

	mSourceX = x;
	mSourceY = y;

	mRunAnimation = false;
	mObjectType = "Projectile";

}

void Projectile::drawUnit(System* aSystem)
{
	aSystem->getDisplay()->draw(mSourceX, mSourceY, &mBullet, 1);
}

void Projectile::update(double time)
{
	setYLoc(mSourceY -= 5);
	
}