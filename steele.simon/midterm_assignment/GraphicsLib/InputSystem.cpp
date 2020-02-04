#include "InputSystem.h"

// This is the default constructo for the class
InputSystem::InputSystem()
{
}





// This function is the default destructor for the class
InputSystem::~InputSystem()
{
	cleanup();
}





// This function initializes the input system whenever called
void InputSystem::init() 
{
	mIsEnterDown = false;
	mIsSpaceDown = false;
	mIsEscapeDown = false;
	mIsLeftButtonDown = false;
}





// This function cleansup and destroys the input system whenever called
void InputSystem::cleanup() 
{
	mIsEnterDown = false;
	mIsSpaceDown = false;
	mIsEscapeDown = false;
	mIsLeftButtonDown = false;
}





// This function gets called in the game loop within the game class and
// checks for input between the last frames
void InputSystem::update() 
{
	ALLEGRO_KEYBOARD_STATE boardState;

	al_get_keyboard_state(&boardState); // Get the current keys that are being pressed


	// The following code finds if any of the keys
	// are being pressed and will fire an event if said key has recently been released

	if (al_key_down(&boardState, ALLEGRO_KEY_ESCAPE))
	{
		mIsEscapeDown = true;
	}
	else if (mIsEscapeDown == true) 
	{
		mIsEscapeDown = false;
		EventSystem::getStaticInstance()->fireEvent(Event(ESCAPE_KEY_RELEASED));
	}

	if (al_key_down(&boardState, ALLEGRO_KEY_ENTER))
	{
		mIsEnterDown = true;
	}
	else if (mIsEnterDown == true) 
	{
		mIsEnterDown = false;
		EventSystem::getStaticInstance()->fireEvent(Event(ENTER_KEY_RELEASED));
	}

	if (al_key_down(&boardState, ALLEGRO_KEY_SPACE))
	{
		mIsSpaceDown = true;
	}
	else if (mIsSpaceDown == true) 
	{
		mIsSpaceDown = false;
		EventSystem::getStaticInstance()->fireEvent(Event(SPACE_KEY_RELEASED));
	}


	ALLEGRO_MOUSE_STATE mouseState;

	al_get_mouse_state(&mouseState); // Get the current mouse state


	// The following code checks if (any) of the mouse buttons have been
	// pressed and will fire events accordingly

	if (mouseState.buttons & 1) // 1 is equal to the left mouse button being held
	{
		mIsLeftButtonDown = true;
	}
	else if (mIsLeftButtonDown == true) 
	{
		mIsLeftButtonDown = false;
		EventSystem::getStaticInstance()->fireEvent(LeftClickPressedEvent(Vector2(mouseState.x, mouseState.y)));
	}


	else if (mouseState.buttons & 2) // 2 is equal to the right mouse button being held
	{
		EventSystem::getStaticInstance()->fireEvent(RightClickPressedEvent(Vector2(mouseState.x,mouseState.y)));
	}
	else if (mouseState.buttons & 4)  // 4 is equal to the middle mouse button being held
	{
		EventSystem::getStaticInstance()->fireEvent(Event(MIDDLE_MOUSE_PRESSED));
	}

	EventSystem::getStaticInstance()->fireEvent(MouseMovedEvent(Vector2(mouseState.x, mouseState.y)));

}