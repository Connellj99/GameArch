#include "InputSystem.h"
#include "System.h"
#include "EventSystem.h"
#include "Event.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

InputSystem::InputSystem()
{
	mLastCursorPosX = 0;
	mLastCursorPosY = 0;
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::update()
{
	string keyButton = mpSystem->getKeyState();
	int mouseButton = mpSystem->getMouseState();

	ALLEGRO_KEYBOARD_STATE currentKeyState = mpSystem->mPlayerKeyboard;
	ALLEGRO_MOUSE_STATE currentMouseState = mpSystem->mPlayerMouse;
	
	int currentCursorPosX = mpSystem->getMouseX();
	int currentCursorPosY = mpSystem->getMouseY();

	if (!inFirstUpdate && al_key_down(&currentKeyState, ALLEGRO_KEY_ENTER) != al_key_down(&mLastKeyState, ALLEGRO_KEY_ENTER))
	{
		bool keyDown;
		if (al_key_down(&currentKeyState, ALLEGRO_KEY_ENTER))
		{
			keyDown = true;
		}
		else
		{
			keyDown = false;
		}
		mpEventSystem->fireEvent(KeyEvent(keyDown, ENTER));	//Group into single event 
	}

	if (!inFirstUpdate && al_key_down(&currentKeyState, ALLEGRO_KEY_SPACE) != al_key_down(&mLastKeyState, ALLEGRO_KEY_SPACE))
	{
		bool keyDown;
		if (al_key_down(&currentKeyState, ALLEGRO_KEY_SPACE))
		{
			keyDown = true;
		}
		else
		{
			keyDown = false;
		}		
		mpEventSystem->fireEvent(KeyEvent(keyDown, SPACE));
	}

	if (!inFirstUpdate && al_key_down(&currentKeyState, ALLEGRO_KEY_ESCAPE) != al_key_down(&mLastKeyState, ALLEGRO_KEY_ESCAPE))
	{
		bool keyDown;
		if (al_key_down(&currentKeyState, ALLEGRO_KEY_ESCAPE))
		{
			keyDown = true;
		}
		else
		{
			keyDown = false;
		}
		mpEventSystem->fireEvent(KeyEvent(keyDown, ESCAPE));
	}

	
	
	if(mLastCursorPosX != currentCursorPosX || mLastCursorPosY != currentCursorPosY)//if (mouseButton == 1) //Left mouse button
	{
			mpEventSystem->fireEvent(MouseEvent(mpSystem->getMouseX(), mpSystem->getMouseY(), LEFT_MOUSE_BUTTON, 1));
	}
	
	if (mouseButton == 2) //Right mouse button
	{
		mpEventSystem->fireEvent(MouseEvent(mpSystem->getMouseX(), mpSystem->getMouseY(), RIGHT_MOUSE_BUTTON, 2));
	}


	mLastCursorPosX = currentCursorPosX;
	mLastCursorPosY = currentCursorPosY;

	mLastKeyState = currentKeyState;
	mLastMouseState = currentMouseState;
	inFirstUpdate = false;

}

void InputSystem::cleanup()
{
	
}

void InputSystem::init(System* gameSystem, EventSystem* eventSystem)
{
	mpSystem = gameSystem;
	mpEventSystem = eventSystem;
}