#ifndef ANIMATION_H
#define ANIMATION_H

#include "Trackable.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

// hold a list of Sprites and the timing information to switch between them
class Animation : public Trackable
{
public:
	// default constructor is never called and I have 0 clue what requires it :(
	Animation();
	Animation(const std::vector<Sprite>& sprites, float speed, bool looping);
	// splits sprite sheet graphics buffer into animation
	Animation(GraphicsBuffer* spriteSheetBuffer, const Vector2D& spriteDimensions, float speed, bool looping);
	// copy constructor is never called but Unit's map of animations requires it :(
	Animation(const Animation& rhs);
	~Animation();

	void update(float curTime);

	Sprite* getCurentSprite() { return &mSprites[mCurSpriteIndex]; }
	void setSpeed(float speed);
	float getSpeed() const { return mSpeed; }
	void setLooping(bool looping) { mLooping = looping; }
private:
	void operator=(const Animation&) = delete;

	std::vector<Sprite> mSprites;
	unsigned int mCurSpriteIndex;

	float mPrevUpdateTime;
	float mSpeed;
	// the numerator of mSpeed, allows speed inputs to look prettier (purely for readability)
	const float SPEED_DAMPING = 50;
	bool mLooping;
};
#endif