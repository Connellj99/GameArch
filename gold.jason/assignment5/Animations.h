#ifndef Animations_h
#define Animations_h

#include <vector>
#include "Trackable.h"
#include "Sprites.h"
#include "GraphicsBuffer.h"

class Animations : public Trackable
{
public:
	//Animations(GraphicsBuffer* spriteBuffer);
	Animations(std::vector<Sprites*> spriteVector);
	~Animations();
	void Update(double time);
	Sprites* getCurrentSprite();
	void SpeedUp(double adjustment);
	void SlowDown(double adjustment);
	void switchLooping();
private:
	std::vector<Sprites*> mAnimationVector;
	int mCurrentSprite;
	int mVectorMax;
	double mTimeUntilFrame;
	double mTimeInfo;
	bool mLooping;
};
#endif // !Animations_h
