#include "InputSystem.h"
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "Event.h"
#include "EventSystem.h"
#include "MouseDownEvent.h"
#include "KeyDownEvent.h"

InputSystem::InputSystem()
	: mpEventQueue(nullptr)
{
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	mIsInitted = true;

	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
}

void InputSystem::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	al_unregister_event_source(mpEventQueue, al_get_mouse_event_source());
	al_unregister_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_destroy_event_queue(mpEventQueue);
	mpEventQueue = nullptr;
}

void InputSystem::update(float curTime)
{
	auto eventSystem = EventSystem::getInstance();

	while(!al_is_event_queue_empty(mpEventQueue))
	{
		ALLEGRO_EVENT allegroEvent;
		al_get_next_event(mpEventQueue, &allegroEvent);

		switch(allegroEvent.type)
		{
		case ALLEGRO_EVENT_MOUSE_AXES:
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			eventSystem->fireEvent(MouseDownEvent(allegroEvent.mouse.button,
				Vector2D(allegroEvent.mouse.x, allegroEvent.mouse.y)));
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			eventSystem->fireEvent(KeyDownEvent(KeyCode(allegroEvent.keyboard.keycode)));
			break;
		case ALLEGRO_EVENT_KEY_UP:
			break;
		default: ;
		}
	}
}
