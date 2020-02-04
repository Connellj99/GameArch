#pragma once
#include "Trackable.h"


class HUD : public Trackable
{
public:

	HUD();
	~HUD() {};

	void update();

private:

	int mPlayerScore;
	int mPlayerLives;


};