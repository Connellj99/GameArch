#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <vector>

//forward declarations
class Sprite;
class GraphicsBuffer;

//constants
const float TIME_PER_FRAME_MODIFIER = 0.05f;

class Animations : public Trackable
{
public:
	Animations(float time, bool canLoop);
	~Animations();

	void updateAnimation(float timeAmt);//function that will simply update the unit

	Sprite* getCurrentSprite();

	void cleanUpSpriteAnims();
	void addSprite(Sprite* spriteToBeAdded);
	void chopSpriteSheet(GraphicsBuffer& passBuffer);//function that will simply update the unit
	void changeAnimationSpeed(bool speedUp,bool speedDown);
	void adjustAnimationSpeed(float adjustmentAmt);

private:
	
	float mTimer = 0.0f;
	float mTimeCount = 0.0f;
	float mTimePerFrame = 0.2f;

	bool mCanLoop;//if the animation can loop

	int mTotalAnimations;//how many animations there currently are
	int mAnimationsX;//how many animations in a row are there. keeps track of X index
	int mAnimationsY;//same as the animationsX

	int mCurrentSpriteIndex;

	std::vector<Sprite*> mpListOfAnimations;
};
#endif