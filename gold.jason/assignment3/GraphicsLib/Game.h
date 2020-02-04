#pragma once

#include "System.h"
//class System;
#include "Timer.h"
#include "PerformanceTracker.h"
#include <string>
using namespace std;

class Game : public Trackable {

private:

	System* mSys = new System;
	bool escape = false;
	Timer* mpTimer;

public:

	Game();
	void init();
	void doLoop();
	void update();
	void input();
	void draw();
	void draw(GraphicsBuffer* buff);
	~Game();
};