#include "Animation.h"

Animation::Animation()
{
	mCurSpriteIndex = 0;
	mPrevUpdateTime = 0;
	mSpeed = 0;
	mLooping = false;
}

Animation::Animation(const std::vector<Sprite>& sprites, float speed, bool looping)
	: mSprites(sprites)
{
	mSprites.shrink_to_fit();
	mCurSpriteIndex = 0;
	mPrevUpdateTime = 0;
	mSpeed = speed;
	mLooping = looping;
}

Animation::Animation(GraphicsBuffer* spriteSheetBuffer, const Vector2D& spriteDimensions, float speed, bool looping)
{
	// create sprites from sprite sheets and store in sprites vector
	for (auto y = 0; y < spriteSheetBuffer->getDimensions().getY(); y += spriteDimensions.getY())
	{
		for (auto x = 0; x < spriteSheetBuffer->getDimensions().getX(); x += spriteDimensions.getX())
		{
			mSprites.push_back(Sprite(spriteSheetBuffer, Vector2D(x, y), spriteDimensions));
		}
	}

	mSprites.shrink_to_fit();
	mCurSpriteIndex = 0;
	mPrevUpdateTime = 0;
	mSpeed = speed;
	mLooping = looping;
}

Animation::Animation(const Animation& rhs)
	: mSprites(rhs.mSprites)
{
	mCurSpriteIndex = rhs.mCurSpriteIndex;
	mPrevUpdateTime = 0;
	mSpeed = rhs.mSpeed;
	mLooping = rhs.mLooping;
}

Animation::~Animation()
{
	mSprites.clear();
}

void Animation::update(float curTime)
{
	if (mCurSpriteIndex < mSprites.capacity() - 1)
	{
		// increment sprite if elapsed time is greater than inverse of speed value (so higher speeds actually increment more)
		if (curTime - mPrevUpdateTime > SPEED_DAMPING / mSpeed)
		{
			mCurSpriteIndex++;
			mPrevUpdateTime = curTime;
		}
	}
	// reset sprite index to beginning if looping is enabled
	else if (mLooping)
	{
		mCurSpriteIndex = 0;
	}
}

void Animation::setSpeed(float speed)
{
	if(speed < 0)
	{
		speed = 0;
	}
	mSpeed = speed;
}
