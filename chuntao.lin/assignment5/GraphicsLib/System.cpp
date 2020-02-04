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
	if (!al_install_keyboard()) {
		cout << "failed to initialize the keyboard!\n";
	}
	if (!al_install_mouse()) {
		cout << "Couldn't install mouse.\n";
	}
}




// This function cleans up and destroys all of the allegro systems
void System::cleanup() 
{
	mCurrentGraphicsSystem.cleanup();
	mIsDisplaying = false; // Set the bool that checks if the program is displaying as false
}





//// This function gets the current keys being pressed
//Keys System::getKeyState() 
//{
//	Keys currentState = KEY_OTHER;
//
//	ALLEGRO_KEYBOARD_STATE boardState;
//
//	al_get_keyboard_state( &boardState ); // Get the current keys that are being pressed
//
//
//	// The following code assigns an enum value for the keys (if any)
//	// that are being pressed
//	if (al_key_down( &boardState, ALLEGRO_KEY_ESCAPE) ) 
//	{
//		currentState = KEY_ESCAPE;
//	}
//	else if (al_key_down( &boardState, ALLEGRO_KEY_F) )
//	{
//		currentState = KEY_F;
//	}
//	else if (al_key_down( &boardState, ALLEGRO_KEY_S) )
//	{
//		currentState = KEY_S;
//	}
//	else if (al_key_down( &boardState, ALLEGRO_KEY_ENTER) )
//	{
//		currentState = KEY_ENTER;
//	}
//	else if (al_key_down(&boardState, ALLEGRO_KEY_SPACE)) 
//	{
//		currentState = KEY_SPACE;
//	}
//
//	return currentState;
//}
//
//
//
//
//
//// This function gets the current mouse buttons being pressed
//Mouse_State System::getMouseState() 
//{
//	ALLEGRO_MOUSE_STATE mouseState;
//
//	al_get_mouse_state( &mouseState );
//	updateMousePosition( Vector2(mouseState.x, mouseState.y) ); // Update the current mouse position 
//
//
//	if ( mouseState.buttons & 1 ) // 1 is equal to the left mouse button being held
//	{
//		return MOUSE_LEFT;
//	}
//	else if ( mouseState.buttons & 2 ) // 2 is equal to the right mouse button being held
//	{
//		return MOUSE_RIGHT;
//	}
//	else if ( mouseState.buttons & 4 )  // 4 is equal to the middle mouse button being held
//	{
//		return MOUSE_MIDDLE;
//	}
//	else 
//	{
//		return MOUSE_NONE;
//	}
//
//	
//}





//// This function gets the current mouse position on the screen
//Vector2 System::getMousePosition() 
//{
//	return mMousePos;
//}





// This function calls to graphics system to flip the display 
// to change frames
void System::flipDisplay() 
{
	mCurrentGraphicsSystem.flip();
}




//
//// This function updates the mouse position, which is updated 
//// on a frame-by-frame basis
//void System::updateMousePosition( Vector2 newPos ) 
//{
//	mMousePos = newPos;
//}





// This function gets the current graphics system attached to the system class
GraphicsSystem System::getGraphicsSystem() 
{
	return mCurrentGraphicsSystem;
}