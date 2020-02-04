#include "Player.h"
#include "Game.h"


// This function is the default constructor for the class 
Player::Player() : Unit()
{
	mUnitType = PLAYER;
}





// This constructor moves the player Unit to a given position
Player::Player(Vector2 newPos) 
{
	mCurrentLocation = newPos;
	mUnitType = PLAYER;
}





// This is the destructor for the class
Player::~Player()
{

}





// This function is the update function for the Player Unit
void Player::update(double newTimeBetweenFrames) 
{
}