#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "Vector2D.h"
#include "Animation.h"
#include "Game.h"

class Unit : public Trackable
{
private:
	//location (x,y)
	Vector2D mLocation;
	
	//animation
	Animation * mpAnimation;
public:
	//constructor
	Unit(int xPos, int yPos);

	//destructor
	~Unit();

	//Update - adjusts the state of the Unit
	void update();

	//Draw - draw animation's current sprite in location of unit
	void draw(int locX, int locY);

	//setAnimation - switch to a new animation
	void setAnimation(Animation * pAnimation);

	//get animation
	Animation * getAnimation() { return mpAnimation; };
};