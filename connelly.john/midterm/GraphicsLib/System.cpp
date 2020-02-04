#include "System.h"
#include <allegro5/allegro_image.h>

System::System()
{
	mpInputSystem = new InputSystem();
	mpGraphicsSystem = new GraphicsSystem();
}

System::~System()
{
	cleanup();

	delete mpGraphicsSystem;
	delete mpInputSystem;
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

	mpInputSystem->init();
	mpGraphicsSystem->init(displayDimensions);
}

void System::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	mpGraphicsSystem->cleanup();
	mpInputSystem->cleanup();

	// cleanup allegro addons
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
}

void System::update(float curTime)
{
	mpInputSystem->update(curTime);
}
