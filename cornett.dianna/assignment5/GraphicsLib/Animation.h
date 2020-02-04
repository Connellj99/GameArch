/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <vector>
#include "Sprite.h"

class Animation : public Trackable
{
private:
	std::vector<Sprite*> mSprites;
	float mTimePerSprite;
	unsigned int mCurrentSpriteIndex = 0;
	bool mShouldLoop;
	double mTimeCounter = 0;

public:

	/*
	Constructor initlizes varibles but does not add any sprites
	*/
	Animation(float timePerSprite, bool shouldLoop);


	/*
	Destructor destorys all sprites
	*/
	~Animation();

	/*
	This function pushes a new sprite onto the end of mpSprites
	*/
	void addSprite(Sprite * sprite);

	/*
	Time per frame is modified by amount.
	*/
	void changeAnimationSpeed(float amount);

	/*
	This function returns the current sprite
	*/
	Sprite * getCurrentSprite();
	

	/*
	This function updates the current sprite index
	*/
	void update(double deltaTime);
	
	/*
	This function reads a spritesheet with a given sheet and hight into the animation
	*/
	void readInSprites(GraphicsBuffer * spriteSheet, int spriteSheetWidth, int spriteSheetHeight);
};