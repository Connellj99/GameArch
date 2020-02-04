#include "System.h"
#include "allegro5/allegro_image.h"
System::System()
{
	//
}

System::~System()
{
	cleanup();
}

void System::init()
{
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	mMouseState = new ALLEGRO_MOUSE_STATE();
	mGraphicsSystem = new GraphicsSystem();
	mGraphicsSystem->init();
}

void System::cleanup()
{
	if (&mGraphicsSystem != nullptr)
	{
		//mGraphicsSystem->cleanUp();
		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		al_shutdown_ttf_addon();
		delete mGraphicsSystem;
		delete mMouseState;
		mGraphicsSystem = nullptr;
		mMouseState = nullptr;
	}
}

bool System::getKeyDown(KeyCode keyCode)
{

	al_get_keyboard_state(&mKeyboardState);
	return al_key_down(&mKeyboardState, keyCode);
}

Mouse System::getButtonDown(MouseCode mouseCode)
{
	al_get_mouse_state(mMouseState);
	Mouse temp;
	temp.down = al_mouse_button_down(mMouseState, mouseCode);
	temp.position = Vector2D(mMouseState->x, mMouseState->y);
	return temp;
}

GraphicsSystem * System::getGraphicsSystem()
{
	return mGraphicsSystem;
}

Vector2D System::getDisplaySize()
{
	return Vector2D(mGraphicsSystem->getWidth(),mGraphicsSystem->getHeight());
}
