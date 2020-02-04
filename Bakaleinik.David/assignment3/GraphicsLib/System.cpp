#include "System.h"

#include <cassert>

using namespace std;

string System::getKeyState()
{
	al_get_keyboard_state(&mPlayerKeyboard);

	if (al_key_down(&mPlayerKeyboard, ALLEGRO_KEY_F))
	{
		//Animation.speedUp();
		return "F";
	}
	else if (al_key_down(&mPlayerKeyboard, ALLEGRO_KEY_S))
	{		
		//Animation.slowDown();
		return "S";
	}
	else if (al_key_down(&mPlayerKeyboard, ALLEGRO_KEY_ESCAPE))
	{	
		return "Esc";
	}
	else if (al_key_down(&mPlayerKeyboard, ALLEGRO_KEY_ENTER))
	{	
		//Unit.changeHead();
		return "Ent";
	}
	return "";
}

bool System::getMouseState(int mouseButton)
{
	bool buttonPressed = false;

	al_get_mouse_state(&mPlayerMouse);

	if (mPlayerMouse.buttons & mouseButton)
	{
		buttonPressed = true;
	}

	return buttonPressed;
}

int System::getMouseX()
{
	return mPlayerMouse.x;
}

int System::getMouseY()
{
	return mPlayerMouse.y;
}

void System::cleanupSystem()
{
	if (mIsInited)
	{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	delete mDisplay;
	
	mIsInited = false;
	}
}
void System::initSystem()
{
	if (!mIsInited)
	{
		mDisplay->initDisplay();

		if (!al_install_keyboard())
		{
			cout << "Error installing keyboadr!" << endl;
			assert(al_install_keyboard());
		}
		if (!al_install_mouse())
		{
			cout << "Error installing mouse!" << endl;
			assert(al_install_mouse());
		}
		mIsInited = true;
	}
	

}


System::System()
{
}

System::~System()
{
	cleanupSystem();
}

System::System(int height, int width)
{
	mDisplay = new GSystem(height, width);
}

void System::sleep(double time)
{
	mDisplay->waitForSeconds(time);
	
}