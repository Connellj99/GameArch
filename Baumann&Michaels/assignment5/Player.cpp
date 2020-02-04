#include "Player.h"

Player::Player()
{

	setInitVals(0,0, 10);
	cout << "init player" << endl;
}

Player::Player(int x, int y, float speed)
{
	setInitVals(x, y, speed);
}

Player::~Player()
{
}

void Player::update(double dt)
{
	if (mCurrentX + mVectX < mLowerBounds[0] && mCurrentX + mVectX > mUpperBounds[0])
		mCurrentX += mVectX;

	if (mCurrentY + mVectY < mLowerBounds[1] && mCurrentY + mVectY > mUpperBounds[1])
		mCurrentY += mVectY;

	Unit::update(dt);
}

void Player::setBounds(float* lowerBounds, float* upperBounds) 
{
	mLowerBounds = lowerBounds;
	mUpperBounds = upperBounds;
}

void Player::setInitVals(int x, int y, float speed)
{
	Unit::Unit();
	mCurrentX = x;
	mCurrentY = y;
	mSpeed = speed;
	mVectX = 0;
	mVectY = 0;
}

void Player::move(int x, int y)
{
	if (x != NONE)
		mVectX = x;
	
	if (y != NONE)
		mVectY = y;
}