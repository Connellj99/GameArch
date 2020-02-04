#pragma once
#include "Sprite.h"
#include "Trackable.h"
#include <vector>
using namespace std;

class Animation : public Trackable
{
public:
	Animation(GraphicsBuffer &spriteSheet, Vector2D spriteDimensions, double switchTime, bool loopAnimation);
	Animation(GraphicsBuffer &spriteSheet, Vector2D spriteDimensions);
	//~Animation();

	Sprite* getCurrentSprite();
	void speedUp(double time);
	void slowDown(double time);
	void update(double frameTime);
	void updateLocation(Vector2D position);
	void changeLoop();

private:
	vector<Sprite> mSpriteVector;
	double mTargetSwichTime = 15;
	double mCurrentTime = 0;
	int mCurrentSprite = 0;
	bool mLoop = true;

};