#include "Animation.h"

Animation::Animation(const std::vector<Sprite*>& sprites, float speed, bool looping)
	: mSprites(sprites)
{
	mSprites.shrink_to_fit();
	mCurSpriteIndex = 0;
	mpTimer = new Timer();
	mpTimer->start();
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
			mSprites.push_back(new Sprite(spriteSheetBuffer, Vector2D(x, y), spriteDimensions));
		}
	}

	mSprites.shrink_to_fit();
	mCurSpriteIndex = 0;
	mpTimer = new Timer();
	mpTimer->start();
	mPrevUpdateTime = 0;
	mSpeed = speed;
	mLooping = looping;
}

Animation::~Animation()
{
	for (auto sprite : mSprites)
	{
		delete sprite;
	}
	delete mpTimer;
}

void Animation::update()
{
	if (mCurSpriteIndex < mSprites.capacity() - 1)
	{
		const auto curUpdateTime = mpTimer->getElapsedTime();
		// increment sprite if elapsed time is greater than inverse of speed value (so higher speeds actually increment more)
		if (curUpdateTime - mPrevUpdateTime > SPEED_DAMPING / mSpeed)
		{
			mCurSpriteIndex++;
			mPrevUpdateTime = curUpdateTime;
		}
	}
	// reset sprite index to beginning if looping is enabled
	else if (mLooping)
	{
		mCurSpriteIndex = 0;
	}
}
