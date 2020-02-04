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

	int mCurrentSprite;
	int mTotalSprites;
public:
	Animation();
	~Animation();
	void addTo(Sprite* newSprite);
	void update();
	Sprite* getCurrentSprite();
	int getTotalSprites();
	Sprite* getSprite(int iter);
	GraphicsBuffer* loadFromBitmap(ALLEGRO_BITMAP* bmp, int width, int height, int x, int y);
};

#endif