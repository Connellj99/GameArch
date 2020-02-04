#include "InputSystem.h"
#include "../EventListener.h"
#include "../Game.h"
#include "../MousePressEvent.h"
#include "../ButtonPressEvent.h"

InputSystem::InputSystem()
{
	init();
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
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

void InputSystem::cleanup()
{
}

void InputSystem::checkInput()
{
	//Start of tracking the mouse
	al_get_mouse_state(&state);

	if (state.buttons == 1)
	{
		//pGame->smurfUnit->setX(state.x);
		//pGame->smurfUnit->setY(state.y);

		//pGame->getInstance()->addSmurf(state.x, state.y);
		pGame->getInstance()->fireEvent(MousePressEvent(state.buttons, state.x, state.y));
	}
	else if (state.buttons == 2)
	{
		//pGame->getInstance()->removeUnitAt(state.x, state.y);
		pGame->getInstance()->fireEvent(MousePressEvent(state.buttons, state.x, state.y));
	}


	//Start of tracking the keyboard
	al_get_keyboard_state(&keyState);

	if (al_key_down(&keyState, ESCAPE_KEY) && !pressed)
	{
		//pGame->getInstance()->shouldExit();
		//pressed = true;
		pGame->getInstance()->fireEvent(ButtonPressEvent(ESCAPE_KEY));
	}

	if (al_key_down(&keyState, F_KEY) && !pressed)
	{
		//pGame->getInstance()->adjustTime(speedUp);
		//pressed = true;
	}

	if (al_key_down(&keyState, S_KEY) && !pressed)
	{
		//pGame->getInstance()->adjustTime(speedDown);
		//pressed = true;
	}

	if (al_key_down(&keyState, ENTER_KEY) && !pressed)
	{
		//pGame->getInstance()->switchAnim();
		//pressed = true;
		pGame->getInstance()->fireEvent(ButtonPressEvent(ENTER_KEY));
	}

	if (al_key_down(&keyState, SPACE_KEY) && !pressed)
	{
		//pGame->getInstance()->enableUnitUpdating();
		pGame->getInstance()->fireEvent(ButtonPressEvent(SPACE_KEY));
	}
}
