#include "System.h"
#include <allegro5/allegro_image.h>

System::System()
	: mKeyboardState(), mMouseState()
{
	mpGraphicsSystem = new GraphicsSystem();
}

System::~System()
{
	cleanup();

	delete mpGraphicsSystem;
}

void System::init(const Vector2D& displayDimensions)
{
	mIsInitted = true;

	// init allegro and its addons
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();

	mpGraphicsSystem->init(displayDimensions);
}

void System::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	mpGraphicsSystem->cleanup();

	// cleanup allegro addons
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
}

bool System::getKeyState(KeyCode keyCode)
{
	// store current state of keyboard
	al_get_keyboard_state(&mKeyboardState);
	// return whether requested key is down in current keyboard state
	return al_key_down(&mKeyboardState, keyCode);
}

MouseState System::getMouseState(int mouseButton)
{
	// store current state of mouse
	al_get_mouse_state(&mMouseState);

	MouseState mouseState;
	mouseState.isDown = al_mouse_button_down(&mMouseState, mouseButton);
	mouseState.location = Vector2D(mMouseState.x, mMouseState.y);
	return mouseState;
}

