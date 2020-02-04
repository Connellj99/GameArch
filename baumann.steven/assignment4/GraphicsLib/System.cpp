#include "System.h"
#include <limits>
System::System() 
{
	mpEventQueue = NULL;
}

System::System(int width, int height, float FPS) : mFramesPerSecond((1.0 / (float)FPS) * 1000)
{
	
	mpGraphicsSystem = new GraphicsSystem(width, height);
	mpTimer = al_create_timer(1.0/1000);
}

void System::init() 
{
	mpGraphicsSystem->init();
	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_display_event_source(mpGraphicsSystem->display));
	al_register_event_source(mpEventQueue, al_get_timer_event_source(mpTimer));
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	
}

void System::draw(int x, int y, Sprite* picture, double scale) 
{
	mpGraphicsSystem->Draw(x, y, picture, scale);
}

Animation* System::createAnimation(GraphicsBuffer* animSheet, vector<GraphicsBuffer*> &targetSheet, int dimensions) 
{
	return mpGraphicsSystem->Slice(animSheet, targetSheet, dimensions);
}

GraphicsBuffer* System::createAnimation(GraphicsBuffer* animSheet, int dimensions)
{
	return NULL;
}

void System::flip() 
{
	mpGraphicsSystem->Flip();
}

int System::waitForEvent() 
{
	ALLEGRO_EVENT ev;
	al_wait_for_event_timed(mpEventQueue, &ev, std::numeric_limits<float>::lowest()); //Check for user input until frame is over
	
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{ 
		switch (ev.mouse.button) {
		case 1: //Left Mouse Button
			mMouseStateX = ev.mouse.x;
			mMouseStateY = ev.mouse.y;
			return eventType::MouseChanged;
			break;
		case 2: //Right Mouse Button
			mMouseStateX = ev.mouse.x;
			mMouseStateY = ev.mouse.y;
			return eventType::RemoveSprite;
			break;
		}
		
	}
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
	{
		switch (ev.keyboard.keycode) 
		{
		case ALLEGRO_KEY_ENTER:
			return eventType::EnterKey;
			break;
		case ALLEGRO_KEY_F:
			return eventType::FKey;
			break;
		case ALLEGRO_KEY_S:
			return eventType::SKey;
			break;
		case ALLEGRO_KEY_ESCAPE:
			return eventType::EscapeKey;
			break;
		case ALLEGRO_KEY_SPACE:
			return eventType::SpaceKey;
			break;
		}	
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) 
	{
		mMouseStateX = ev.mouse.x;
		mMouseStateY = ev.mouse.y;
		return eventType::NoEvent;
	}
	return eventType::NoEvent;
}

int* System::getMouseState() 
{
	int* mousePos = new int[2];
	mousePos[0] = mMouseStateX;
	mousePos[1] = mMouseStateY;

	return mousePos;
}

void System::cleanup() 
{
	delete mpGraphicsSystem;
	al_destroy_event_queue(mpEventQueue);
	al_destroy_timer(mpTimer);
}

System::~System() 
{
	delete mpGraphicsSystem;
}