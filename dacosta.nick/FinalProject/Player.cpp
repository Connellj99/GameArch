#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "DirectionKeys.h"
#include "UnitTypes.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsSystem.h"
#include "Level.h"
#include "LevelManager.h"
#include "Unit.h"
#include "Player.h"

// Constructor.
Player::Player()
{
	mType = PLAYER;

	return;
}

// Destructor.
Player::~Player()
{
	return;
}

// Set the destination of the player.
void Player::setDestination(int _positionX, int _positionY)
{
	mDestinationX = _positionX;
	mDestinationY = _positionY;

	return;
}

// Set the destination to go to when its current destination is reached.
void Player::setQueueDestination(int _positionX, int _positionY)
{
	mQueueDestinationX = _positionX;
	mQueueDestinationY = _positionY;

	return;
}

// Set the move speed multiplier.
void Player::setSpeed(double _speed)
{
	mSpeed = _speed;

	return;
}

// Get the move speed.
double Player::getSpeed(double _deltaTime)
{
	return OPTIMAL_FRAME_RATE / mDistance * _deltaTime * mSpeed;;
}

// Get the move speed multiplier.
double Player::getSpeed()
{
	return mSpeed;
}

// Get the current destination x coordinate.
int Player::getDestinationX()
{
	return mDestinationX;
}

// Get the current destination y coordinate.
int Player::getDestinationY()
{
	return mDestinationY;
}

// Get the queued destination x coordinate.
int Player::getQueueDestinationX()
{
	return mQueueDestinationX;
}

// Get the queued destination y coordinate.
int Player::getQueueDestinationY()
{
	return mQueueDestinationY;
}

// Check if the given position is colliding with this segment.
bool Player::collision(int _positionX, int _positionY)
{
	// Calculate the difference in position.
	int xPositionDifference = _positionX - mPositionX;
	int yPositionDifference = _positionY - mPositionY;

	// Return weather or not the collision is within the dimensions of the sprite.
	return xPositionDifference <= getWidth() && xPositionDifference >= 0 && yPositionDifference <= getHeight() && yPositionDifference >= 0;
}

// Set the movement direction.
void Player::setDirection(int _direction)
{
	mDirection = _direction;

	return;
}

// Set the queued movement direction.
void Player::setQueueDirection(int _direction)
{
	mQueueDirection = _direction;

	return;
}

// Get the current movement direction.
int Player::getDirection()
{
	return mDirection;
}

// Get the queued movement direction.
int Player::getQueueDirection()
{
	return mQueueDirection;
}

// Set the movement distance.
void Player::setDistance(int _distance)
{
	mDistance = _distance;

	return;
}

// Get the movement distance.
int Player::getDistance()
{
	return mDistance;
}

// Move in the direction the player is facing towards the destination.
void Player::move(double _deltaTime, LevelManager* _pLevelManager)
{
	if (mMove)
	{
		double speed = getSpeed(_deltaTime);

		_pLevelManager->getLevel()->removePlayerLocation(mPositionX, mPositionY);

		switch (mDirection)
		{
			case SOUTH:
				mPositionY += speed;
				if (mPositionY >= mDestinationY)
				{
					mPositionY = mDestinationY;
				}
				break;
			case WEST:
				mPositionX -= speed;
				if (mPositionX <= mDestinationX)
				{
					mPositionX = mDestinationX;
				}
				break;
			case NORTH:
				mPositionY -= speed;
				if (mPositionY <= mDestinationY)
				{
					mPositionY = mDestinationY;
				}
				break;
			case EAST:
				mPositionX += speed;
				if (mPositionX >= mDestinationX)
				{
					mPositionX = mDestinationX;
				}
				break;
			default:
				break;
		}

		int gridWidth = 0;
		int gridHeight = 0;

		_pLevelManager->getLevel()->getGridDimensions(gridWidth, gridHeight);

		if (mPositionX > gridWidth + mDistance / 2)
		{
			mPositionX = ((mPositionX % gridWidth) - mDistance);
			mDestinationX = (mDestinationX % gridWidth) - mDistance;
			mQueueDestinationX = (mQueueDestinationX % gridWidth) - mDistance;
		}
		else if (mPositionX < 0 - mDistance / 2)
		{
			mPositionX += gridWidth + (mDistance / 2);
			mDestinationX += gridWidth;
			mQueueDestinationX += gridWidth;
		}

		_pLevelManager->getLevel()->addPlayerLocation(mPositionX, mPositionY);
	}

	return;
}

// Update the destination and queued destination of the head segment.
void Player::updateDestination()
{
	switch (mDirection)
	{
		case SOUTH:
			mDestinationY += mDistance;
			break;
		case WEST:
			mDestinationX -= mDistance;
			break;
		case NORTH:
			mDestinationY -= mDistance;
			break;
		case EAST:
			mDestinationX += mDistance;
			break;
		default:
			break;
	}

	switch (mQueueDirection)
	{
		case SOUTH:
			mQueueDestinationY += mDistance;
			break;
		case WEST:
			mQueueDestinationX -= mDistance;
			break;
		case NORTH:
			mQueueDestinationY -= mDistance;
			break;
		case EAST:
			mQueueDestinationX += mDistance;
			break;
		default:
			break;
	}
	
	return;
}

void Player::updateDirection()
{
	mDirection = mQueueDirection;

	return;
}

void Player::turnOffMovement()
{
	mMove = false;
	return;
}

void Player::turnOnMovement()
{
	mMove = true;
	return;
}

bool Player::canMove()
{
	return mMove;
}
