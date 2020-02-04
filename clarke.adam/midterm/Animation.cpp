#include "Animation.h"

Animation::Animation()
{
	mCurSpriteIndex = 0;
	mPrevUpdateTime = 0;
	mSpeed = 0;
	mLooping = false;
	mNumSprites = 0;
}

Animation::Animation(const std::vector<Sprite>& sprites, float speed, bool looping)
	: mSprites(sprites)
{
	mSprites.shrink_to_fit();
	mCurSpriteIndex = 0;
	mPrevUpdateTime = 0;
	mSpeed = speed;
	mLooping = looping;
	mNumSprites = mSprites.end() - mSprites.begin();
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
	mNumSprites = mSprites.end() - mSprites.begin();
}

Animation::Animation(const Animation& rhs)
	: mSprites(rhs.mSprites)
{
	mCurSpriteIndex = rhs.mCurSpriteIndex;
	mPrevUpdateTime = 0;
	mSpeed = rhs.mSpeed;
	mLooping = rhs.mLooping;
	mNumSprites = mSprites.end() - mSprites.begin();
}

Animation::~Animation()
{
	mSprites.clear();
}

void Animation::update(float curTime)
{
	// increment sprite if elapsed time is greater than inverse of speed value (so higher speeds actually increment more)
	if (curTime - mPrevUpdateTime > SPEED_DAMPING / mSpeed)
	{
		increment(1);
		mPrevUpdateTime = curTime;
	}
}

void Animation::setSpeed(float speed)
{
	if (speed < 0)
	{
		speed = 0;
	}
	mSpeed = speed;
}

void Animation::increment(unsigned int numFrames)
{
	mCurSpriteIndex += numFrames;

	if (mCurSpriteIndex >= mNumSprites)
	{
		mCurSpriteIndex = mLooping ? mCurSpriteIndex % mNumSprites : mNumSprites - 1;
	}
}
