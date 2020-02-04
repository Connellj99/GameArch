#include "InputSystem.h"

InputSystem::InputSystem()
{
	initInputSystem();
}

InputSystem::~InputSystem()
{
}

void InputSystem::initInputSystem()
{
}

void InputSystem::updateInput()
{
	//call the functions to get input from allegro
	getKeyState();
	getMouseState();
}

// This function gets the current keys being pressed
void InputSystem::getKeyState()
{
	ALLEGRO_KEYBOARD_STATE boardState;

	al_get_keyboard_state(&boardState); // Get the current keys that are being pressed
										// The following code assigns an enum value for the keys (if any)
										// that are being pressed

	//Escape input
	if (al_key_down(&boardState, ALLEGRO_KEY_ESCAPE))
	{
		mHitEscape = true;
	}
	else if (mHitEscape == true)
	{
		mHitEscape = false;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(ESCAPE_BUTTON_RELEASED));
	}

	//Space Input for toggle animations
	if (al_key_down(&boardState, ALLEGRO_KEY_SPACE))
	{
		mHitSpace = true;//it was pressed
	}
	else if (mHitSpace == true)
	{
		mHitSpace = false;//no longer pressed
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(SPACE_BUTTON_RELEASED));
	}

	//Enter Input for flipping animations
	if (al_key_down(&boardState, ALLEGRO_KEY_ENTER))
	{
		mHitEnter = true;
	}
	else if (mHitEnter == true)
	{
		mHitEnter = false;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(ENTER_BUTTON_RELEASED));
	}
}

// This function gets the current mouse buttons being pressed
void InputSystem::getMouseState()
{
	ALLEGRO_MOUSE_STATE mouseState;
	
	al_get_mouse_state(&mouseState);//get the mouse state 
	
	if (mouseState.buttons & 1) // 1 is equal to the left mouse button being held
	{
		EventSystem::getStaticEventSysInstance()->fireEvent(LeftClickEvent(Vector2(mouseState.x,mouseState.y)));//get the static instance and then fire the event with the vec 2 class and pass in the current mouse positions
	}
	else if (mouseState.buttons & 2) // 2 is equal to the right mouse button being held
	{
		EventSystem::getStaticEventSysInstance()->fireEvent(RightClickEvent(Vector2(mouseState.x, mouseState.y)));//get the static instance and then fire the event with the vec 2 class and pass in the current mouse positions
	}
	else
	{
		//nothin
	}
}