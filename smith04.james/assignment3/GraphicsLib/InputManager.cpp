#include "InputManager.h"
#include "../Game.h"

InputManager::InputManager()
{
	init();
}

InputManager::~InputManager()
{
	cleanup();
}

void InputManager::init()
{

	if (!al_install_mouse())
	{
		std::cout << "Error initializing the mouse!\n";
	}
	if (!al_install_keyboard())
	{
		std::cout << "Error initializing the keyboard!\n";
	}


}

void InputManager::cleanup()
{
}

void InputManager::checkInput()
{
	//Start of tracking the mouse
	al_get_mouse_state(&state);

	if (state.buttons == 1)
	{
		pGame->smurfUnit->setX(state.x);
		pGame->smurfUnit->setY(state.y);
	}


	//Start of tracking the keyboard
	al_get_keyboard_state(&keyState);

	if (al_key_down(&keyState, ESCAPE_KEY) && !pressed)
	{
		pGame->shouldExit();
		//pressed = true;
	}

	if (al_key_down(&keyState, F_KEY) && !pressed)
	{
		pGame->adjustTime(speedUp);
		//pressed = true;
	}

	if (al_key_down(&keyState, S_KEY) && !pressed)
	{
		pGame->adjustTime(speedDown);
		//pressed = true;
	}

	if (al_key_down(&keyState, ENTER_KEY) && !pressed)
	{
		pGame->switchAnim();
		//pressed = true;
	}
}
