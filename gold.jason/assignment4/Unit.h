/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
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

	// Update the animation.
	void update(double _deltaTime);

	// Draw at a the current coordinates.
	void draw(GraphicsSystem* _pGraphicsSystem);

	// Set the animtation clip.
	void setAnimation(Animation* _pAnimation);

	// Set the position.
	void setPosition(float _positionX, float _positionY);

	//add animations
	void addAnimation(Animation* addAnim);

	//swap animation
	void swapAnim();

	//init
	void initUnit();

	// Get the x and y coordinates.
	float getPositionX();
	float getPositionY();

private:

	// The current animation clip.
	Animation* mpAnimation = nullptr;

	// The x coordinate.
	float  mPositionX = 0;

	// The y coordinate.
	float mPositionY = 0;
};