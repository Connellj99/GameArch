#pragma once

#include "GraphicsSystem.h"

class Unit : public Trackable {

private:

	int locX = 0;
	int locY = 0;
	Animation* smurfAnim = nullptr;
	Animation* deanAnim = nullptr;

public:

	Unit();
	void draw();
	void update();
	Animation setAnimation();
	~Unit();
};