/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class CreateUnitEvent :
	public Event
{
public:
	// Create a new create unit event.
	CreateUnitEvent(int _positionX, int _positionY);

	// Get the position.
	void getPosition(int& _x, int& _y);

private:
	// The x position.
	int mPositionX = 0;
	// The y position.
	int mPositionY = 0;
};

class RemoveUnitEvent :
	public Event
{
public:
	// Remove a unit event.
	RemoveUnitEvent(int _positionX, int _positionY);

	// Get the position.
	void getPosition(int& _x, int& _y);

private:
	// The x position.
	int mPositionX = 0;
	// The y position.
	int mPositionY = 0;
};

class ToggleUnitAnimationEvent :
	public Event
{
public:
	// Toggle the animation.
	ToggleUnitAnimationEvent() : Event(EventType(TOGGLE_UNIT_ANIMATION)) { return; }
};

class ToggleUnitSpriteEvent :
	public Event
{
public:
	// Toggle the sprite.
	ToggleUnitSpriteEvent() : Event(EventType(TOGGLE_UNIT_SPRITE)) { return; }
};

class ChangeUnitDirectionEvent :
	public Event
{
public:
	// Move a unit event.
	ChangeUnitDirectionEvent(int _direction);

	// Get the position.
	int getDirection();

private:
	// The moving direction.
	int mDirection = WEST;
};

class CollisionUnitEvent :
	public Event
{
public:
	// Unit collision event with type.
	CollisionUnitEvent(int _type);

	int getType();

private:
	int mType = NONE;
};

