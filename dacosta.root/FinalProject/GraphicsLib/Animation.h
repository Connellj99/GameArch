/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

// Default animation speed at 12 frames per second.
const double DEFAULT_ANIMATION_SPEED = 12;

/// <summary>
///		An animation.
/// </summary>
/// <seealso cref="Trackable" />
class Animation :
	public Trackable
{
public:
	// Constructor.
	Animation();

	// Destructor.
	~Animation();

	// Clean up the animation.
	void cleanUp();

	// Initialize the animation clip with sprites.
	void initialize(Sprite* _pSprites, int _size, int _speed = DEFAULT_ANIMATION_SPEED);

	// Update the animation.
	void update(double _deltaTime);

	// Set the animation clip.
	void setAnimationClip(Sprite* _pSprites, int _size);

	// Get the current sprite in the animation clip.
	Sprite getCurrentSprite();

	// Get the current animation clip.
	Sprite* getCurrentClip();

	// Speed adjuster.
	void adjustSpeed(double _speedMultiplier);

private:
	// The animation clip.
	Sprite* mpAnimationClip = nullptr;

	// The current sprite index from the animation clip.
	int mCurrentIndex = 0;

	// Animation speed.
	double mSpeed = 0.0;

	// Time since the last animation frame.
	double mDeltaTime = 0;

	// Animation clip size.
	int mClipSize = 0;

	// Animation looping.
	bool mLoop = true;
};