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
	void setPosition(float _positionX, float _positionY);

	// Get the x and y coordinates.
	float getPositionX();
	float getPositionY();

	// Get the width and height.
	int getWidth();
	int getHeight();
	
	// Check if there is a collision at this unit.
	bool collision(int _positionX, int _positionY);

	// Toggle the animate setting on/off.
	void toggleAnimate();

private:
	// The current animation clip.
	Animation* mpCurrentAnimation;
	
	// List of all animations.
	std::vector<Animation*> mpAnimations;

	// Animate tracker.
	bool mAnimate = true;

	// The x coordinate.
	float  mPositionX = 0;

	// The y coordinate.
	float mPositionY = 0;
};