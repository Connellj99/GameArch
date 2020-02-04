#ifndef ANIMATION_H
#define ANIMATION_H

// Standard Library includes
#include <vector>

// Graphics Library includes
#include <Sprite.h>

const double  DEFAULT_SPEED = 300.0;

class Animation : public Trackable
{
public:

	// Constructors
	Animation();
	Animation( GraphicsBuffer * spriteSheet, int spritesPerRow, int spritesPerColumn,  Vector2 displayDimensions, Vector2 spriteDimensions);

	// Destructors
	~Animation();
	void cleanupAnimation();

	// Update functions
	void update( double framesPassed );
	void updateSpritePositions( Vector2 newPos );

	// Mutators
	void addSprite( Sprite * spriteToAdd );
	void adjustCurrentSpeed( double speedToBeAdded );

	// Accessors
	Sprite * getCurrentSprite();

private:

	// Local update functions
	void updateSprite();

	// Booleans
	bool mShouldLoop;
	bool mHasCleanedUp;

	// Vectors
	vector<Sprite*> mListOfSprites;

	// Integers
	int mCurrentIndex;

	// Doubles
	double mTargetTime;
	double mTimeElapsed;

};



#endif // !ANIMATION_H

