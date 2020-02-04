#ifndef SYSTEM_H
#define SYSTEM_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>
#include <vector>
#include "GraphicsSystem.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Vector2D.h"

class System : public Trackable
{
	friend class Game;

public:
	System();
	~System();
	//initializers
	void initGraphicSys();
	void initAllegro();

	//clean
	void cleanUpSystem();
	void cleanAllegro();

	//getters
	void getKeyState();//get the user key state
	void getKeyState(bool unitOnScreen);//get the user key state, but also takes in a bool if the unit is on screen
	void getMouseState();//get the user mouse state, default
	void getMouseState(bool unitOnScreen);//get the user mouse state, but also takes in a bool if the unit is on screen

	bool getSpeedUpStatus();
	bool getSpeedDownStatus();
	bool getAnimationSwitchStatus();
	bool getMoveSpriteStatus() { return mCanMoveSprite; };//return the current mouse Y position

	GraphicsSystem* getGraphicSystem();

	Vector2D returnMousePos() { return mMousePos; };//return the vector2D of mouseposition

	enum InputKeys
	{
		KEY_F = ALLEGRO_KEY_F,//key that will eventually speed up animation
		KEY_S = ALLEGRO_KEY_S,//key that will eventually slow down animation
		KEY_ENTER = ALLEGRO_KEY_ENTER,//key that will eventually switch between animations
		KEY_ESCAPE = ALLEGRO_KEY_ESCAPE,//key that will eventually close the application
		MOUSE_LEFT_CLICK = RI_MOUSE_LEFT_BUTTON_DOWN,//mouse click that will eventually place/move smurfs
	};

	
private:

	GraphicsSystem* mpGraphicSys;//pointer to graphicSystem object

	ALLEGRO_KEYBOARD_STATE mKeyBoardState;//used for getting the state of the keyboard 
	ALLEGRO_MOUSE_STATE mMouseState;//same but for mouse

	
	Vector2D mMousePos;//vector2 that will store the mouseposition when mouse clicked

	//booleans to check if the game can run, if we can speed/swap/move animations or sprites

	bool mGameDone = false;//bool that will basically tell program when to quit
	bool mSpeedGameUp = false;//bool that will tell if we can speed up
	bool mSpeedGameDown = false;//or speed down 
	bool mSwitchAnims = false;//bool that will tell if its time to swap animations

	bool mCanMoveSprite = false;//bool to tell if we can move the sprite.
};
#endif