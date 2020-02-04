/*
Conner Root
EGP 310 - 01
*/

#include "System.h"

System::System()
{
}

// Init / Cleanup
void System::init(int w, int h)
{
	if (!mInited)
	{
		al_init();
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		
		mpGraphicSystem = new GraphicsSystem();
		mpGraphicSystem->init(w, h);

		mpInputSystem = new InputSystem();
		mpInputSystem->init();

		mInited = true;
	}
}
void System::cleanup()
{
	if (mInited)
	{
		delete mpGraphicSystem;
		delete mpInputSystem;
		mInited = false;

		al_shutdown_ttf_addon();
		al_shutdown_font_addon();
		al_shutdown_image_addon();
	}
}

// Wait function
void System::wait(float time)
{
	al_rest(time);
}

// Destructor
System::~System()
{
	cleanup();
}