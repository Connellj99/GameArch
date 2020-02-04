#include "InputSystem.h"
#include "../EventSystem.h"
#include "../MouseEvent.h"
#include "../KeyEvent.h"
InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	if (!mIsCleaned)
	{
		cleanup();
	}
}

InputSystem::InputSystem(GraphicsSystem* displaySystem) 
{
	mIsCleaned = false;
	mpEventQueue = nullptr;
	mpTimer = al_create_timer(1.0 / 1000);
	init(displaySystem, mpTimer);
}


void InputSystem::init(GraphicsSystem* displaySystem, ALLEGRO_TIMER* mpTimer) 
{
	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_display_event_source(displaySystem->display));
	al_register_event_source(mpEventQueue, al_get_timer_event_source(mpTimer));
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
}

int* InputSystem::getMouseState() 
{
	int* mousePos = new int[2];
	mousePos[0] = mMouseStateX;
	mousePos[1] = mMouseStateY;
	return mousePos;
}

void InputSystem::cleanup()
{
	if (!mIsCleaned)
	{
		al_destroy_event_queue(mpEventQueue);
		al_destroy_timer(mpTimer);
	}
	
}

void InputSystem::update() 
{
	ALLEGRO_EVENT ev;
	al_wait_for_event_timed(mpEventQueue, &ev, std::numeric_limits<float>::lowest()); //Check for user input until frame is over

	EventSystem* fireSystem = EventSystem::getInstance();

	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		fireSystem->fireEvent(MouseEvent(Vector2D(ev.mouse.x, ev.mouse.y), MouseButtonType::MOUSE_OVER));
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		switch (ev.mouse.button) {
		case 1: //Left Mouse Button
			mMouseStateX = ev.mouse.x;
			mMouseStateY = ev.mouse.y;
			fireSystem->fireEvent(MouseEvent(Vector2D(ev.mouse.x, ev.mouse.y), MouseButtonType::LEFT_MOUSE));
			break;
		case 2: //Right Mouse Button
			mMouseStateX = ev.mouse.x;
			mMouseStateY = ev.mouse.y;
			fireSystem->fireEvent(MouseEvent(Vector2D(ev.mouse.x, ev.mouse.y), MouseButtonType::RIGHT_MOUSE));
			break;
		}

	}
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_ENTER:
			fireSystem->fireEvent(KeyEvent(ENTER_KEY));
			break;
		case ALLEGRO_KEY_F:
			fireSystem->fireEvent(KeyEvent(F_KEY));
			break;
		case ALLEGRO_KEY_S:
			fireSystem->fireEvent(KeyEvent(S_KEY));
			break;
		case ALLEGRO_KEY_ESCAPE:
			fireSystem->fireEvent(KeyEvent(ESCAPE_KEY));
			break;
		case ALLEGRO_KEY_SPACE:
			fireSystem->fireEvent(KeyEvent(SPACE_KEY));
			break;
		case ALLEGRO_KEY_UP:
			fireSystem->fireEvent(KeyEvent(UP_KEY));
			break;
		case ALLEGRO_KEY_LEFT:
			fireSystem->fireEvent(KeyEvent(LEFT_KEY));
			break;
		case ALLEGRO_KEY_DOWN:
			fireSystem->fireEvent(KeyEvent(DOWN_KEY));
			break;
		case ALLEGRO_KEY_RIGHT:
			fireSystem->fireEvent(KeyEvent(RIGHT_KEY));
			break;
		}
	}
	if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_ENTER:
			fireSystem->fireEvent(KeyEvent(ENTER_KEY_UP));
			break;
		case ALLEGRO_KEY_F:
			fireSystem->fireEvent(KeyEvent(F_KEY_UP));
			break;
		case ALLEGRO_KEY_S:
			fireSystem->fireEvent(KeyEvent(S_KEY_UP));
			break;
		case ALLEGRO_KEY_ESCAPE:
			fireSystem->fireEvent(KeyEvent(ESCAPE_KEY_UP));
			break;
		case ALLEGRO_KEY_SPACE:
			fireSystem->fireEvent(KeyEvent(SPACE_KEY_UP));
			break;
		case ALLEGRO_KEY_UP:
			fireSystem->fireEvent(KeyEvent(UP_KEY_UP));
			break;
		case ALLEGRO_KEY_LEFT:
			fireSystem->fireEvent(KeyEvent(LEFT_KEY_UP));
			break;
		case ALLEGRO_KEY_DOWN:
			fireSystem->fireEvent(KeyEvent(DOWN_KEY_UP));
			break;
		case ALLEGRO_KEY_RIGHT:
			fireSystem->fireEvent(KeyEvent(RIGHT_KEY_UP));
			break;
		}
	}



}