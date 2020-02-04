#pragma once
#include "System.h"
#include "Animation.h"
#include <vector>
#include "Trackable.h"
#include "Vector2D.h"
using namespace std;


class Unit : public Trackable
{
public:
	Unit();
	Unit(Animation animation, Vector2D position);
	Unit(vector<Animation> animation, Vector2D position);
	Unit(Animation animation);
	Unit(vector<Animation> animation);
	~Unit();

	void update();
	void updateLocation(Vector2D newPosition);
	void swapAnimations();
	void draw();
	Animation getCurrentAnimation();

private:
	Vector2D mPosition = (0, 0);
	vector<Animation> mAnimationsVec;
	int mCurrentAnimation = 0;
	double mFrameTime = 16.6666666667;
	float mScale = 1;
};