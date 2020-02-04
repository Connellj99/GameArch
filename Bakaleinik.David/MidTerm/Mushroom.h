#pragma once
#include "Unit.h"


class Mushroom : public Unit
{
private:

	std::vector<Sprite> mSpriteVector;
	int mMushroomHP;

	Sprite mCurrentSprite;

public:

	Mushroom(std::vector<Sprite> sprites, int x, int y);
	~Mushroom() {};

	void looseHP() { mMushroomHP--; showDamage(); };
	void showDamage();
	int getHP() { return mMushroomHP; };
	void drawUnit(System* aSystem);
};