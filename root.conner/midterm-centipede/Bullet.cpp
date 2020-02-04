/*
Conner Root
EGP 310 - 01
*/

#include "Bullet.h"
#include "Game.h"
#include "EventSystem.h"
#include "DeleteEvent.h"

// Constructor
Bullet::Bullet()
{
}
Bullet::Bullet(int x, int y, int maxY, Animation* a, int s)
{
	mXPos = x;
	mYPos = y;
	mpAnim = a;
	mSpeed = s;
	mMaxYPos = maxY;
}

// Returns true if out of screen
bool Bullet::checkOutOfBounds()
{
	if (mYPos <= mMaxYPos)
		return true;
	else
		return false;
}

// Shoot the bullet
void Bullet::shoot()
{
	if (!mActive)
	{
		mActive = true;
		mXPos = mpParent->getXPos() + 10;
		mYPos = mpParent->getYPos() - 1;
	}
}

// Update
void Bullet::reset()
{
	mActive = false;
	mXPos = 0;
	mYPos = 780;
}

void Bullet::update()
{
	mpAnim->update();

	// Move it
	if (mActive)
	{
		// If shot then move up if in bounds
		if (!checkOutOfBounds())
		{
			mYPos -= mSpeed;
			EventSystem::getInstance()->fireEvent(DeleteEvent(mXPos, mYPos));
		}
		else
			reset();
	}
}

// Draw
void Bullet::draw()
{
	Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mXPos, mYPos, mpAnim->getCurrentSprite(), 1.0);
}