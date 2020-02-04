/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <Animation.h>
#include <vector>
#include <iostream>
#include "Position.h"
#include "System.h"

class Unit : public Trackable
{

private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	bool mIsAnimating = true;

	std::vector<Animation *> mAnimations;
	unsigned int mCurrentAnimation = 0;

public:

	//Default constructor
	Unit()
	{
	};

	//Constructor that takes vector of animations and position
	Unit(std::vector<Animation *> animations, Position pos, int width, int heights);

	//Create a unit at a given position with no animations
	Unit(Position pos, int width, int height);

	//Destroy the Unit
	~Unit();

	//Update the unit
	void update(double deltaTime);

	//Draw the current animation centered on its positon
	void draw(System * system);


	//Add an animation to the Unit
	void addAnimation(Animation * animation);

	//Change the animation speed by amount
	void changeAnimationSpeed(double amount);

	
	//Check if a given position is inside the unit
	bool positionIsInUnit(Position pos);
	

	//GETTERS
	//Return the current animation
	Animation * getCurrentAnimation();

	//Calculate a position that in the center of the sprite
	Position getCenteredPosition();

	//Getters for X and Y
	int getX()
	{
		return mX;
	};

	int getY()
	{
		return mY;
	};


	//SETTERS
	//Go to the next animation
	void setAnimation();

	//Set the position
	void setPosition(Position pos);

	//Check if the unit should animate 
	void setIsAnimating(bool isAnimating);

};