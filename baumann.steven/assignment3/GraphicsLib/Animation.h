#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Trackable.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>
#include <allegro5/allegro.h>


using namespace std;

class Animation :public Trackable
{
private:
	vector<Sprite*> mSpriteSheet;
	Timer mAnimTimer;
	double mLastTime;

	int mCurrentSprite;
	int mTotalSprites;
	int mCurrentSpeed;
	int mDefaultSpeed;
public:
	Animation();
	~Animation();
	void addTo(Sprite* newSprite);
	void update();
	Sprite* getCurrentSprite();
	Sprite* getSprite(int iter);
	void speedUp();
	void slowDown();
	void loadFromBitmap(ALLEGRO_BITMAP* bmp, int width = 64, int height = 60, int x = 0, int y = 0);
};

#endif