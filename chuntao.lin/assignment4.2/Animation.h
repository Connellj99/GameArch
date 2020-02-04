#ifndef ANIMATION_H
#define ANIMATION_H

// Standard Library includes
#include <vector>

// Graphics Library includes
#include <Sprite.h>
#include "Game.h"

const double  DEFAULT_SPEED = 100.0;

class Animation : public Trackable
{
public:

	// Constructors
	Animation();//default constructor
	Animation( Sprite spriteSheet, int spritesPerRow, int spritesPerColumn,  Vector2 displayDimensions, Vector2 spriteDimensions );//take in the sprite with the appropriate dimensions.
	
	// Destructors
	~Animation();

	// Update functions
	void update( double framesPassed );
	void updateSpritePositions( Vector2 newPos );

	// Mutators
	void addSprite( Sprite * spriteToAdd );
	void adjustCurrentSpeed( double speedToBeAdded );
	void toggleCurrentSpeed();//stop animations or resume them

	// Accessors
	Sprite * getCurrentSprite();

	void cleanAnimation();//clean the animations

private:

	// Local update functions
	void updateSprite();

	// Booleans
	bool mShouldLoop;

	// Vectors
	vector<Sprite*> mpListOfSprites;

	// Integers
	int mCurrentIndex;

	// Doubles
	double mTargetTime;
	double mTimeElapsed;
};



#endif // !ANIMATION_H

