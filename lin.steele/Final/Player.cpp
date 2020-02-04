#include "Player.h"
#include "Game.h"


// This function is the default constructor for the class 
Player::Player() : Unit()
{
	mUnitType = PLAYER;
	mVelocity = 0;
	mMaxJumpForce = -1.5 * JUMP_FORCE;
	mIsJumping = false;
	mInMidAir = false;
	mBounce = false;
	mIsMoving = false;
	mCurrentDirection = MOVING_RIGHT;
}





// This constructor moves the player Unit to a given position
Player::Player(Vector2 newPos) 
{
	mCurrentLocation = newPos;
	mUnitType = PLAYER;
	mVelocity = 0;
	mMaxJumpForce = -1.5 * JUMP_FORCE;
	mIsJumping = false;
	mInMidAir = false;
	mBounce = false;
	mIsMoving = false;
	mCurrentDirection = MOVING_RIGHT;
}





// This is the destructor for the class
Player::~Player()
{

}





// This function is the update function for the Player Unit
void Player::update(double newTimeBetweenFrames) 
{
	mInMidAir = true;

	if (isAnimationStopped == false)
	{
		if (mIsMoving == false) 
		{
			mCurrentAnimations[mCurrentAnimationIndex]->resetAnimationIndex();
		}
		else 
		{
			// The following code updates the current frame of the animation
			mCurrentAnimations[mCurrentAnimationIndex]->update(newTimeBetweenFrames);
		}
	}

	// Check for collision here
	mVelocity += GRAVITY_SCALE;


	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > mCurrentLocation.mX - Game::getStaticInstance()->getPlayerBounds().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < mCurrentLocation.mX + Game::getStaticInstance()->getPlayerBounds().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > (mCurrentLocation.mY + mVelocity) - Game::getStaticInstance()->getPlayerBounds().mY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < (mCurrentLocation.mY + mVelocity) + Game::getStaticInstance()->getPlayerBounds().mY
			)
		{
			if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < mCurrentLocation.mY && Game::getStaticInstance()->getUnitManager()->getUnit(i)->getCurrentUnitType() == QUESTION_BLOCK)
			{
				Game::getStaticInstance()->getUnitManager()->getUnit(i)->swapAnimation(NAME_OF_EMPTY_QUESTION_BLOCK);
				mBounce = false;
			}
			else if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < mCurrentLocation.mY && Game::getStaticInstance()->getUnitManager()->getUnit(i)->getCurrentUnitType() == BRICK_BLOCK)
			{
				Game::getStaticInstance()->getUnitManager()->destroyUnit(i);
				mBounce = false;
			}
			else if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > mCurrentLocation.mY && Game::getStaticInstance()->getUnitManager()->getUnit(i)->getCurrentUnitType() == GOOMBA) 
			{
				Game::getStaticInstance()->getTextManager()->getText(NAME_OF_SCORE_AMOUNT_TEXT)->addScore(100);//add whatever score amt
				Game::getStaticInstance()->getUnitManager()->destroyUnit(i);//destroy unit
				mBounce = true;//player can bounce
			}
			else if (mIsJumping == false)
			{
				mInMidAir = false;
				mBounce = false;
			}

			if (mBounce == true)
			{
			
				mVelocity -= 1.5 * JUMP_FORCE;//substract from velocity the JUMP force times what multiplier we want bounce force by

				if (mVelocity < mMaxJumpForce)
				{
					mVelocity += 1.5 * JUMP_FORCE;//if it gets too much, this will act as a ceiling and limit the drastic bounce.
				}
			}
			else
				mVelocity = 0;
		}
	}

	if (mInMidAir) 
	{
		switch (mCurrentDirection)
		{
		case MOVING_LEFT:
			swapAnimation(NAME_OF_PLAYER_JUMP_LEFT);
			break;
		case MOVING_RIGHT:
			swapAnimation(NAME_OF_PLAYER_JUMP);
			break;
		default:
			break;
		}
	}
	else 
	{
		switch (mCurrentDirection)
		{
		case MOVING_LEFT:
			swapAnimation(NAME_OF_PLAYER_WALKING_LEFT);
			break;
		case MOVING_RIGHT:
			swapAnimation(NAME_OF_PLAYER);
			break;
		default:
			break;
		}
	}

	// Is the player about to jump?
	if (mIsJumping) 
	{
		// Set the velocity to the force of a jump
		mVelocity = -JUMP_FORCE;
		mIsJumping = false;
	}

	moveToPosition(Vector2(mCurrentLocation.mX, mCurrentLocation.mY + mVelocity));
	mIsMoving = false;
}





// This function changes the velocity such that the player jumps
void Player::jump() 
{
	// Is the player grounded?
	if (mVelocity == 0) 
	{
		
		// If yes, then let the player jump
		mIsJumping = true;
	}
}





// This function moves the player unit right
void Player::movePlayerLeft() 
{
	bool canMove = true;

	double minX = (mCurrentLocation.mX - WALK_SPEED) - Game::getStaticInstance()->getPlayerBounds().mX;
	double maxX = (mCurrentLocation.mX - WALK_SPEED) + Game::getStaticInstance()->getPlayerBounds().mX;
	double minY = mCurrentLocation.mY - Game::getStaticInstance()->getPlayerBounds().mY - 1;
	double maxY = mCurrentLocation.mY + Game::getStaticInstance()->getPlayerBounds().mY - 1 ;

	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++) 
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > minX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < maxX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > minY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < maxY
			)
		{

			canMove = false;
		}
	}

	if (canMove) 
	{
		mIsMoving = true;
		mCurrentDirection = MOVING_LEFT;
		moveToPosition(Vector2(mCurrentLocation.mX - WALK_SPEED, mCurrentLocation.mY));
	}
}





// This function moves the player unit right
void Player::movePlayerRight() 
{
	bool canMove = true;

	double minX = (mCurrentLocation.mX + WALK_SPEED) - Game::getStaticInstance()->getPlayerBounds().mX;
	double maxX = (mCurrentLocation.mX + WALK_SPEED) + Game::getStaticInstance()->getPlayerBounds().mX;
	double minY = mCurrentLocation.mY - Game::getStaticInstance()->getPlayerBounds().mY - 1;
	double maxY = mCurrentLocation.mY + Game::getStaticInstance()->getPlayerBounds().mY - 1;

	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > minX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < maxX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > minY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < maxY
			)
		{
			canMove = false;
		}
	}

	if (canMove)
	{
		mIsMoving = true;
		mCurrentDirection = MOVING_RIGHT;
		moveToPosition(Vector2(mCurrentLocation.mX + WALK_SPEED, mCurrentLocation.mY));
	}
}