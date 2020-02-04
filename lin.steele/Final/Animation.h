#ifndef ANIMATION_H
#define ANIMATION_H

// Standard Library includes
#include <vector>

// Graphics Library includes
#include <Sprite.h>

const double  DEFAULT_SPEED = 100.0;

class Animation : public Trackable
{
public:

	// Constructors
	Animation();
	Animation( string name, GraphicsBuffer * spriteSheet, int spritesPerRow, int spritesPerColumn,  Vector2 displayDimensions, Vector2 spriteDimensions);

	// Destructors
	~Animation();
	void cleanupAnimation();

	// Update functions
	void update( double framesPassed );
	void updateSpritePositions( Vector2 newPos );
	void updateSprite();

	// Mutators
	void addSprite( Sprite * spriteToAdd );
	void adjustCurrentSpeed( double speedToBeAdded );
	void resetAnimationIndex();

	// Accessors
	Sprite * getCurrentSprite();
	string getAnimationName();

private:

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

	// Strings
	string mNameOfAnimation;

};



#endif // !ANIMATION_H

