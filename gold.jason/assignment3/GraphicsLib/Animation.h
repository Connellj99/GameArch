#pragma once

#include "System.h"

class Animation : public Trackable {

private:

	//Create an array to store each sprite.
	Sprite smurfSprites[4 * 4];
	Sprite deanSprites[4 * 4];
	//timing info?
	bool mSpriteState;
	bool animLoop;

public:

	Animation();
	void startAnim();
	void update();
	Sprite getCurrentSprite();
	void speedAnim();
	void slowAnim();
	~Animation();

};