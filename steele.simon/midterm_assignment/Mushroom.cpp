#include "Mushroom.h"
#include "Game.h"



// This function is the default constructor for the class
Mushroom::Mushroom() : Unit()
{
	mCurrentLocation = Vector2(0, 0);
	isAnimationStopped = false;
	mUnitType = MUSHROOM;
	mHealth = Game::getStaticInstance()->getInitialHealthOfMushroom();
}





// This constructor initializes all values based on a given position
Mushroom::Mushroom(Vector2 newPos)
{
	mCurrentLocation = newPos;
	isAnimationStopped = false;
	mUnitType = MUSHROOM;
	mHealth = Game::getStaticInstance()->getInitialHealthOfMushroom();
}





// This function is the destructor for the class
Mushroom::~Mushroom()
{
}





// This function is the Update function for this class
void Mushroom::update(double newTimeBetweenFrames)
{
	// The following code is the collision checker for this class
	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX >= mCurrentLocation.mX - Game::getStaticInstance()->getMushroomDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX <= mCurrentLocation.mX + Game::getStaticInstance()->getMushroomDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY >= mCurrentLocation.mY - Game::getStaticInstance()->getMushroomDimensions().mY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY <= mCurrentLocation.mY + Game::getStaticInstance()->getMushroomDimensions().mY
			) 
		{
			// Is the colliding object a bullet?
			if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getCurrentUnitType() == BULLET)
			{
				// Destroy the Bullet
				Game::getStaticInstance()->getUnitManager()->destroyUnit(i);
				
				// Take away one health and change the animation
				mHealth -= 1;
				swapAnimation();

				// Does the Unit have any health?
				if (mHealth <= 0)
				{
					// If no, destroy the Unit
					destroyThisGameObject(Game::getStaticInstance()->getUnitManager());
				}
			}
		}
	}
}