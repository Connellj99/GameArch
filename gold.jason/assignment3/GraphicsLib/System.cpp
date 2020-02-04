#include "System.h"


System::System()
{
	mGraphicSys = new GraphicsSystem();
	eventQueue = NULL;
}

void System::initSys()
{
	mGraphicSys->initialize(800, 600);
	eventQueue = al_create_event_queue();
	al_install_keyboard();
	al_install_mouse();
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	if (!eventQueue) {
		cout << "failed to create event_queue!" << endl;
	}
}

System::~System()
{
	mGraphicSys->cleanUp();
}

void System::getKeyState()
{
	// Constantly check for keyboard activity
	ALLEGRO_KEYBOARD_STATE keyState;

	al_get_keyboard_state(&keyState);
	if (al_key_down(&keyState, ALLEGRO_KEY_F)) {
		//speed up animation
		cout << "FASTER!!!!!!!!" << endl;
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_S)) {
		//slow down animation
		cout << "SLOWER!!!!!!!!" << endl;
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_ENTER)) {
		//swap animation
		cout << "SWAP!!!!!!!!" << endl;
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
		//close the program
		mGraphicSys->cleanUp();
		mGraphicSys->~GraphicsSystem();
		quick_exit(0);
	}
}

bool System::getMouseState()
{
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		return true;
	}
	else {
		return false;
	}
}

void System::draw(GraphicsBuffer* buff) 
{
	mGraphicSys->drawBG(buff, 0, 0, 800, 600, 1.0f);
}