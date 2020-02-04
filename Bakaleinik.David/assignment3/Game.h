#pragma once
#include <string>

#include "Trackable.h"

class Unit;
class System;
class GBuffer;
class Animation;
class Sprite;

class Game : public Trackable		//The class which holds all systems and has the game loop
{
private:

	System *mpGameSystem;
	Unit* mpPlayerUnit;
	Sprite* mpGameBackground;

	GBuffer* mpDeanSheet;
	GBuffer* mpSmurfSheet;
	GBuffer* mpBackgroundBuffer;

	Animation* mpDeanSmurf;
	Animation* mpNormalSmurf;


	double mTargetTime;
	int mDisplayX;
	int mDisplayY;

public:

	void initGame(int x, int y, std::string filename);
	void cleanupGame();

	Game();
	Game(double fps);
	~Game();

	void runGameLoop();

};

extern Game* gpGame;