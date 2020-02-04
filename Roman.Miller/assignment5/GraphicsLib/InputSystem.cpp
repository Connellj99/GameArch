#include "InputSystem.h"
#include "EventSystem.h"
#include "Event.h"
#include "KeyEvent.h"
#include "ClickEvent.h"
#include <allegro5/allegro.h>

InputSystem::InputSystem()
{
	al_init();
	al_install_keyboard();
	al_install_mouse();
	mpMouseState = new ALLEGRO_MOUSE_STATE();
}

InputSystem::~InputSystem()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	delete mpMouseState;
	mpMouseState = nullptr;
}

void InputSystem::update()
{
	Key currentKey;
	Mouse currentMouse;
	
		//Mouse Stuff
	al_get_mouse_state(mpMouseState);

	currentMouse.leftDown = al_mouse_button_down(mpMouseState, Left_Click);
	currentMouse.rightDown = al_mouse_button_down(mpMouseState, Right_Click);
	currentMouse.position = Vector2D(mpMouseState->x, mpMouseState->y);

		//Key Stuff
	al_get_keyboard_state(&mKeyboardState);

	currentKey.fDown = al_key_down(&mKeyboardState, F);
	currentKey.sDown = al_key_down(&mKeyboardState, S);
	currentKey.enterDown = al_key_down(&mKeyboardState, ENTER);
	currentKey.escapeDown = al_key_down(&mKeyboardState, ESCAPE);
	currentKey.spaceDown = al_key_down(&mKeyboardState, SPACE);


	//Fire Events
	EventSystem::getInstance()->fireEvent(ClickEvent(currentMouse));
	EventSystem::getInstance()->fireEvent(KeyEvent(currentKey));
}
