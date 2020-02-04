#ifndef GAME_H
#define GAME_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>
#include <vector>

#include "System.h"
#include "Animations.h"
#include <PerformanceTracker.h>
#include <MemoryTracker.h>

//forward declarations
class System;
class Unit;

//constants
const float CONVERT_MS_TO_SEC = 1000.0f;

class Game : public Trackable
{
public:

	Game();
	~Game();

	void initGameSystems();//used to init allegro and systems and graphioc systems

	void drawStartingData(std::string filePath, std::string filePath2,std::string filePath3);//takes in the filepath for the background and the initial spritesheet

	void gameLoop();

	void cleanUpGame();

	void getUserInput();
	void drawCurrentData();//draws the current state of the game
	void adjustGameState();

	void initializeSmurfs(GraphicsBuffer* spriteObj,int spriteNum);//takes in a graphicsbuffer but also a spriteNum, whic indicates which spritesheet should be cut.

private:

	System* mpGameSystem;//create the system object

	//graphic buffer pointer objects
	GraphicsBuffer* mpBackgroundBuff;
	GraphicsBuffer* mpSpriteBuff;
	GraphicsBuffer* mpSprite2Buff;

	
	std::vector<Unit*> mpSpriteUnitVector;//vector that holds units
	std::vector<Animations*> mpAnimationVector;//vector that holds animations

	//animation pointer objects
	Animations* mpSpriteOneAnimation;//this will be for smurf
	Animations* mpSpriteTwoAnimation;//this will be for smurf dean

	float mSleepAmount = 16.7f;//represents in miliseconds the sleep amount
	bool mUnitOnScreen = false;
};
extern Game *gGameObj;
#endif