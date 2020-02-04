#include "Bullet.h"
#include "Game.h"



// This function is the default constructor for the class
Bullet::Bullet() : Unit()
{
	mUnitType = BULLET;
}





// This constructor initializes all values based on a given position
Bullet::Bullet(Vector2 newPos) 
{
	mCurrentLocation = newPos;
	isAnimationStopped = false;
	mUnitType = BULLET;
}





// This function is the default destructor for the class
Bullet::~Bullet()
{
}





// This function is the update function for this class
void Bullet::update(double newTimeBetweenFrames ) 
{
	// Move the Bullet by that certain amount
	moveToPosition(Vector2(mCurrentLocation.mX, mCurrentLocation.mY - Game::getStaticInstance()->getBulletSpeed()));

	// Is the bullet out of bounds?
	if (mCurrentLocation.mY <= 0) 
	{
		// If yes, destroy the bullet
		destroyThisGameObject(Game::getStaticInstance()->getUnitManager());
	}
}