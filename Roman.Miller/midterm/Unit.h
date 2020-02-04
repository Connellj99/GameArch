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
	Unit(Animation animation, Vector2D position, string type);
	Unit(vector<Animation> animation, Vector2D position, string type);
	Unit(Animation animation, string type);
	Unit(vector<Animation> animation, string type);
	~Unit();

	void update();
	void updateLocation(Vector2D newPosition);
	void swapAnimations();
	void draw();
	void pausePlayAnimation();
	Animation getCurrentAnimation();
	Vector2D getPosition();
	string getType() { return mType; };

private:
	Vector2D mPosition = (0, 0);
	//Poissibly go down the vec backwards and set each to the position of the one before it. only change the head
	vector<Animation> mAnimationsVec;
	int mCurrentAnimation = 0;
	double mFrameTime = 16.6666666667;
	float mScale = 1;
	string mType;
};