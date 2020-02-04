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
	mHitLeftArrow = false;
	mHitRightArrow = false;
	mHitUpArrow = false;
	mHitDownArrow = false;
}

void InputSystem::updateInputGame()
{
	//call the functions to get input from allegro
	getKeyStateGame();//keyboard input that isn't arrows
	getArrowState();//keyboard input for just arrows
	//getMouseState();//mouse input
}

void InputSystem::updateInputStart()
{
	getKeyState();
}

void InputSystem::updateInputEnd()
{
	getKeyStateEnd();
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

void InputSystem::getKeyStateGame()
{
	ALLEGRO_KEYBOARD_STATE boardState;

	al_get_keyboard_state(&boardState); // Get the current keys that are being pressed
										// The following code assigns an enum value for the keys (if any)
										// that are being pressed

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

void InputSystem::getKeyStateEnd()
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
	
	if (al_key_down(&boardState, ALLEGRO_KEY_R))
	{
		mHitR = true;
	}
	else if (mHitR == true)
	{
		mHitR = false;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(R_BUTTON_RELEASED));
	}
}

void InputSystem::getArrowState()
{
	ALLEGRO_KEYBOARD_STATE arrowState;

	al_get_keyboard_state(&arrowState); // Get the current keys that are being pressed
										// The following code assigns an enum value for the keys (if any)
										// that are being pressed

	//Left Arrow
	if (al_key_down(&arrowState, ALLEGRO_KEY_LEFT) && mHitRightArrow == false)
	{
		//set these to false so now player could move in either of these directions
		mHitUpArrow = false;
		mHitDownArrow = false;

		//has hit left arrow, and therefore cannot move in the right direction
		mHitLeftArrow = true;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(LEFT_ARROW_RELEASED));
	}
	//Right Arrow
	if (al_key_down(&arrowState, ALLEGRO_KEY_RIGHT) && mHitLeftArrow == false)
	{
		//set these to false so now player could move in either of these directions
		mHitUpArrow = false;
		mHitDownArrow = false;

		//has hit right arrow,  and therefore cannot move in the left direction
		mHitRightArrow = true;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(RIGHT_ARROW_RELEASED));
	}
	//Up Arrow
	if (al_key_down(&arrowState, ALLEGRO_KEY_UP) && mHitDownArrow == false)
	{
		//set these to false so now player could move in either of these directions
		mHitLeftArrow = false;
		mHitRightArrow = false;
		
		//has hit up arrow,  and therefore cannot move in the down direction
		mHitUpArrow = true;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(UP_ARROW_RELEASED));
	}
	//Down Arrow
	if (al_key_down(&arrowState, ALLEGRO_KEY_DOWN) && mHitUpArrow == false)
	{
		//set these to false so now player could move in either of these directions
		mHitLeftArrow = false;
		mHitRightArrow = false;

		//has hit down arrow, and therefore cannot move in the up direction
		mHitDownArrow = true;
		EventSystem::getStaticEventSysInstance()->fireEvent(Event(DOWN_ARROW_RELEASED));
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