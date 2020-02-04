/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/// <summary>
///		A game entity.
/// </summary>
/// <seealso cref="Trackable" />

class Unit :
	public Trackable
{
public:
	// Constructor.
	Unit();

	// Constructor with unit type.
	Unit(int _type);

	// Destructor.
	~Unit();

	// Clean up the unit.
	void cleanUp();

	// Update the animation.
	void update(double _deltaTime);

	// Draw at a the current coordinates.
	void draw(GraphicsSystem* _pGraphicsSystem);

	// Set the animtation clip.
	void setAnimation(Animation* _pAnimation);

	// Add animation clip.
	void addAnimation(Animation* _pAnimation);

	// Switch between animations.
	void switchAnimation();

	// Set the position.
	void setPosition(int _positionX, int _positionY);

	// Set the position centered on the unit.
	void setCenteredPosition(int _positionX, int _positionY);

	// Get the x and y coordinates.
	int getPositionX();
	int getPositionY();

	// Get the width and height.
	int getWidth();
	int getHeight();

	// Toggle the animate setting on/off.
	void toggleAnimate();

	int getType();

protected:
	// The current animation clip.
	Animation* mpCurrentAnimation;
	
	// List of all animations.
	std::vector<Animation*> mpAnimations;

	// Animate tracker.
	bool mAnimate = true;

	// The x coordinate.
	int  mPositionX = 0;

	// The y coordinate.
	int mPositionY = 0;

	int mType = NONE;
};