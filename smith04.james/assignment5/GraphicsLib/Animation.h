#pragma once
#include "Sprite.h"

class Animation : public Trackable
{
private:
	Sprite** mpAnimList;
	int size;
	int currentIndex;
	//timing info (to be done when I can figure that out better)
	bool shouldLoop;

	friend class Unit;
public:
	Animation();
	~Animation();

	void loadSprites(GraphicsBuffer* spriteMap, int rows, int columns);
	void update();
	Sprite* getCurrentSprite();
	void adjustSpeed(float adjustment);

	void cleanUp();
};