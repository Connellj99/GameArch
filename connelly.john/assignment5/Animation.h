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
	Animation(const std::vector<Sprite*>& sprites, float speed, bool looping);
	// splits sprite sheet graphics buffer into animation
	Animation(GraphicsBuffer* spriteSheetBuffer, const Vector2D& spriteDimensions, float speed, bool looping);
	~Animation();

	void update();

	Sprite* getCurentSprite() const { return mSprites[mCurSpriteIndex]; }
	void setSpeed(float speed) { mSpeed = speed; }
	float getSpeed() const { return mSpeed; }
	void setLooping(bool looping) { mLooping = looping; }
private:
	Animation(const Animation&);
	void operator=(const Animation&);

	std::vector<Sprite*> mSprites;
	unsigned int mCurSpriteIndex;

	Timer* mpTimer;
	float mPrevUpdateTime;
	float mSpeed;
	// the numerator of mSpeed, allows speed inputs to look prettier (purely for readability)
	const float SPEED_DAMPING = 50;
	bool mLooping;
};
#endif