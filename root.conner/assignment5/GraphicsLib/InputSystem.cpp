/*
Conner Root
EGP 310 - 01
*/

#include "InputSystem.h"
#include "EventSystem.h"
#include "MouseClickEvent.h"
#include "KeyDownEvent.h"

InputSystem::InputSystem()
{
}

// Init / Cleanup
void InputSystem::init()
{
	if (!mInited)
	{
		al_install_keyboard();
		al_install_mouse();

		mpEventQueue = al_create_event_queue();
		al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
		al_register_event_source(mpEventQueue, al_get_mouse_event_source());

		mInited = true;
	}
}

void InputSystem::cleanup()
{
	if (mInited)
	{
		al_unregister_event_source(mpEventQueue, al_get_mouse_event_source());
		al_unregister_event_source(mpEventQueue, al_get_keyboard_event_source());
		al_destroy_event_queue(mpEventQueue);

		al_uninstall_mouse();
		al_uninstall_keyboard();

		mpEventQueue = nullptr;

		mInited = false;
	}
}

// Update
void InputSystem::update()
{
	EventSystem* EventSysInst = EventSystem::getInstance();

	while (!al_event_queue_is_empty(mpEventQueue))
	{
		ALLEGRO_EVENT tempEvt;
		al_get_next_event(mpEventQueue, &tempEvt);

		switch (tempEvt.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			EventSysInst->fireEvent(MouseClickEvent(tempEvt.mouse.button, tempEvt.mouse.x, tempEvt.mouse.y));
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			EventSysInst->fireEvent(KeyDownEvent(KeyCode(tempEvt.keyboard.keycode)));
			break;
		default:
			break;
		}
	}
}

InputSystem::~InputSystem()
{
	cleanup();
}