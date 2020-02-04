#include "InputSystem.h"
#include "Event.h"
#include "MouseClickEvent.h"
#include "KeyPressEvent.h"
#include "EventSystem.h"
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
	cleanup();
}

//creates the event queue and registers the sources of the events
void InputSystem::init()
{
	mIsInit = true;
	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());

}

//destroys the event queue
void InputSystem::cleanup()
{
	if (mIsInit) 
	{
		al_unregister_event_source(mpEventQueue, al_get_keyboard_event_source());
		al_unregister_event_source(mpEventQueue, al_get_mouse_event_source());
		al_destroy_event_queue(mpEventQueue);

		mIsInit = false;
	}
	else 
	{
		return;
	}
}

//determines what is added to the event queue and fires the appropriate events
void InputSystem::update(double time)
{
	auto eventSystem = EventSystem::getInstance();

	while (!al_is_event_queue_empty(mpEventQueue)) 
	{
		ALLEGRO_EVENT event;
		al_get_next_event(mpEventQueue, &event);

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) 
		{
			eventSystem->fireEvent(MouseClickEvent(event.mouse.button, event.mouse.x, event.mouse.y));
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			break;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			eventSystem->fireEvent(KeyPressEvent(event.keyboard.keycode));
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			break;
		}
		else 
		{
			break;
		}
	}
}
