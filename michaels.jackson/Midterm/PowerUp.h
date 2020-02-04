/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "GameEvents.h"
#include "Unit.h"
#include "Trackable.h"

class PowerUpObj :public Unit
{
public:
	PowerUpObj(Point, PowerUp, GraphicsBuffer *, float);

	PowerUp getPower() { return mPower; }

	virtual void draw(float scale = 1) override;

private:
	PowerUp mPower;

	float mTargetSize;

};