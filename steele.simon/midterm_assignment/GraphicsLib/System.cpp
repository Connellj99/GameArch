#include "System.h"





// This function is the default constructor for this class
System::System()
{
	mCurrentGraphicsSystem = GraphicsSystem();
}





// This function is the destructor for this class
System::~System()
{
	if ( mIsDisplaying ) 
	{
		cleanup();
	}
}





// This function initializes all of the allegro systems
void System::init( int screenWidth, int screenHeight )
{
	mCurrentGraphicsSystem.init( screenWidth, screenHeight );
	mCurrentGraphicsSystem.flip();

	mIsDisplaying = true; // Set the bool that checks if the program is displaying as true
}





// This function initializes all of the allegro-based add-ons
// If they can't be found, the will print the error to the console
void System::initializeSystems() 
{
	if (!al_init())
	{
		cout << "error initting Allegro\n";
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
	}
	if (!al_install_keyboard()) 
	{
		cout << "failed to initialize the keyboard!\n";
	}
	if (!al_install_mouse()) 
	{
		cout << "Couldn't install mouse.\n";
	}
}




// This function cleans up and destroys all of the allegro systems
void System::cleanup() 
{
	mCurrentGraphicsSystem.cleanup();
	mIsDisplaying = false; // Set the bool that checks if the program is displaying as false
}





// This function calls to graphics system to flip the display 
// to change frames
void System::flipDisplay() 
{
	mCurrentGraphicsSystem.flip();
}





// This function gets the current graphics system attached to the system class
GraphicsSystem System::getGraphicsSystem() 
{
	return mCurrentGraphicsSystem;
}