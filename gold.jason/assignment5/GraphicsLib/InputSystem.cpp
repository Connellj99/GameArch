#include "InputSystem.h"
#include "Event.h"
#include "EventSystem.h"

InputSystem::InputSystem()
{
	mEventSys = EventSystem::getEventSys();
	mpEventQueue = nullptr;
	initInputSys();
}

InputSystem::~InputSystem()
{

}

void InputSystem::initInputSys()
{
	if (!(al_install_keyboard()))
	{
		std::cout << "error initting Allegro\n";
		system("pause");
		return;
	}
	if (!(al_install_mouse()))
	{
		std::cout << "mouse  not installed\n";
	}
	mpEventQueue = al_create_event_queue();
	if (mpEventQueue == nullptr)
	{
		std::cout << "event queue not installed\n" << std::endl;
	}

	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());

}

void InputSystem::getKeyState()
{
	ALLEGRO_EVENT event;
	al_get_next_event(mpEventQueue, &event);
	if(event.type = ALLEGRO_EVENT_KEY_DOWN)
	{
		if(event.keyboard.keycode == ALLEGRO_KEY_SPACE)
		{
			mEventSys->fireEvent(SPACE_KEY);
		}
		else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			mEventSys->fireEvent(ENTER_KEY);
		}
		else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			mEventSys->fireEvent(ESC_KEY);
		}
	}
}

void InputSystem::getMouseState()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	if(mouseState.buttons == 1)
	{
		mEventSys->fireEvent(LEFT_CLICK);
	}
	else if (mouseState.buttons == 2) 
	{
		mEventSys->fireEvent(RIGHT_CLICK);
	}
}

Vector2D InputSystem::getMouseLocation()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	Vector2D mouseLoc(mMouseState.x, mMouseState.y);
	return mouseLoc;
}

void InputSystem::update()
{
	getMouseState();
	getKeyState();
}

void InputSystem::cleanUpInput()
{
	mEventSys = nullptr;
	al_destroy_event_queue(mpEventQueue);
}

EventSystem * InputSystem::getEventSys()
{
	return mEventSys->getEventSys();
}



