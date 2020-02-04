#include "Player.h"
#include "System.h"


Player::Player(Sprite* playerSprite)
{
	mPlayerSprite = *playerSprite;
	mObjectType = "Player";
	mNumLives = 3;
	mRunAnimation = false;
}

void Player::checkLife()
{
	if (mLifeScore >= 12000)
	{
		addLife();
		mLifeScore = 0;
	}
}

void Player::drawUnit(System* theSystem)
{
	theSystem->getDisplay()->draw(mSourceX, mSourceY, &mPlayerSprite, 1);
}