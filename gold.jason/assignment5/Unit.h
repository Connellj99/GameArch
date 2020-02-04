#ifndef Unit_h
#define Unit_h
#include <Trackable.h>
#include <vector>
#include "Animations.h"
class Unit : public Trackable
{
public:
	Unit();
	Unit(int xLoc, int yLoc,float scale, std::vector<Sprites*> animVector);
	~Unit();
	void update(double time);
	void draw();
	void setAnimation();
	void addAnimations(std::vector<Sprites*> animVector);
	void setLocX(int x);
	void setLocY(int y);
	void animationCleanUp();

	Animations* getCurrentAnimation()
	{
		return mpCurrentAnimation;
	};
	int getCurrentAnimIndex()
	{
		return mCurrentAnimationsIndex;
	};
	int getLocX()
	{
		return mLocX;
	};
	int getLocY()
	{
		return mLocY;
	};
private:
	int mLocX;
	int mLocY;
	float mScale;
	int mCurrentAnimationsIndex;
	int mMaxAnimations;
	Animations* mpCurrentAnimation;
	std::vector<Animations*> mAnimationSets;

	/*
	notes for unit
	should draw itself
	*/

};

#endif // !Unit_h
