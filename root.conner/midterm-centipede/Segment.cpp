/*
Conner Root
EGP 310 - 01
*/

#include "Segment.h"
#include "Game.h"
#include "EventSystem.h"

// Constructor
Segment::Segment(int x, int y, int s, int mX, int mY, Animation* a)
{
	mXPos = x;
	mYPos = y;
	mSpeed = s;
	mMaxX = mX;
	mMaxY = mY;
	mpAnim = a;

	mLastY = 0;
}

// Update
void Segment::update()
{
	mpAnim->update();

	// Check if moving down or to the side
	if (mMoveDown)
	{
		// If moving down, move down
		mYPos += mSpeed;

		// Check if moved down sufficiently 
		if (mYPos > mLastY + 25 && mYPos > 24)
		{
			mYPos -= mYPos % 24;
			mLastY = mYPos;
			mMoveDown = false;
		}
	}
	else
	{
		/*
		 * If moving sideways, move correct direction
		 * If it hit the side, signal to move down then reverse direction
		*/
		if (mLeft)
		{
			mXPos -= mSpeed;
			if (mXPos <= 0)
			{
				collide();
			}
		}
		else
		{
			mXPos += mSpeed;
			if (mXPos >= mMaxX - 24)
			{
				collide();
			}
		}
	}

	// Reset to top
	if (mYPos >= mMaxY - 15)
	{
		reset();
	}
}

void Segment::collide()
{
	mMoveDown = true;

	if (mLeft)
	{
		mLeft = false;
	}
	else
	{
		mLeft = true;
	}
}

void Segment::reset()
{
	mXPos = mMaxX / 2;
	mYPos = 0;
	mLastY = 0;
	mMoveDown = true;
}

// Draw
void Segment::draw()
{
	Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mXPos, mYPos, mpAnim->getCurrentSprite(), 1.0);
}