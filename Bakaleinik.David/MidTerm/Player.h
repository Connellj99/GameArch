#pragma once
#include "Trackable.h"
#include "Sprite.h"
#include "Unit.h"

class System;


class Player : public Unit
{
public:

	Player(Sprite* playerSprite);
	~Player() {};

	void drawUnit(System* theSystem);

	int getNumLives() { return mNumLives; };
	void looseLife() { mNumLives--; };
	
	Sprite* getPlayerSprite() { return &mPlayerSprite; };

	void setPlayerX(int newX) { mSourceX = newX; };
	void setPlayerY(int newY) { mSourceY = newY; };

	void addLife() { mNumLives++; };

	void checkLife();
	void addLifeScore(int amount) { mLifeScore += amount; };

private:

	Sprite mPlayerSprite;

	int mNumLives;
	int mLifeScore;

};