#include "System.h"
#include "System.h"

System::System()
{
	//stub
	initGraphicSys();
}

System::~System()
{
	mpGraphicSys->cleanGraphicSys();
	delete mpGraphicSys;
	cleanAllegro();
}

void System::initGraphicSys()
{
	initAllegro();
	mpGraphicSys = new GraphicsSystem(800, 600);
}

void System::initAllegro()
{
	//initialize all the allegro and its respective add ons
	if (!al_init())
	{
		std::cout << "allegro couldnt initialize";
	}
	if (!al_install_keyboard())//initialize the use of keyboard
	{
		std::cout << "keyboard was not installed";
	}
	if (!al_install_mouse())
	{
		std::cout << "mouse was not installed";
	}
	if (!al_init_image_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return;
	}
	if (!al_install_audio())
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_reserve_samples(1))
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_init_font_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_acodec_addon())
	{
		std::cout << "error initting acodec\n";
		system("pause");
		return;
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "error initting primitives\n";
		system("pause");
		return;
	}
}

void System::cleanUpSystem()
{
	delete mpGraphicSys;
}

void System::cleanAllegro()
{

	al_uninstall_system();
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();

}

void System::getKeyState()
{
	al_get_keyboard_state(&mKeyBoardState);//get the keyboard state. really looks if any button on keyboard was pressed

	if (al_key_down(&mKeyBoardState, ALLEGRO_KEY_ESCAPE))//if the key pressed was escape then close application
	{
		std::cout << "Escape pressed";
		system("cls");
		mGameDone = true;
	}

	else if (al_key_down(&mKeyBoardState, KEY_F))//if the key pressed was F then speed up animation
	{
		std::cout << "F pressed";
		system("cls");
		
		mSpeedGameUp = true;
	}

	else if (al_key_down(&mKeyBoardState, ALLEGRO_KEY_S))//if the key pressed was S then slow down animation
	{
		std::cout << "S pressed";
		system("cls");
		mSpeedGameDown = true;
	}

	else if (al_key_down(&mKeyBoardState, ALLEGRO_KEY_ENTER))//if the key pressed was enter then switch animations
	{
		std::cout << "Enter pressed";
		system("cls");

		if (mSwitchAnims == true)//if the switchAnims is currenting true, meaning if you can switch. set it to false. That way in my code, it will prevent the sprite from constantly swapping.
		{
			mSwitchAnims = false;
		}
		else//if the switch anim is false but enter was pressed, then yes we can swap animations.
			mSwitchAnims = true;
	}
	else
	{

	}
}

void System::getKeyState(bool unitOnScreen)
{
	al_get_keyboard_state(&mKeyBoardState);//get the keyboard state. really looks if any button on keyboard was pressed

	if (unitOnScreen == true)
	{
		if (al_key_down(&mKeyBoardState, ALLEGRO_KEY_ESCAPE))//if the key pressed was escape then close application
		{
			mGameDone = true;
		}

		else if (al_key_down(&mKeyBoardState, KEY_F))//if the key pressed was F then speed up animation
		{
			mSpeedGameUp = true;
		}

		else if (al_key_down(&mKeyBoardState, ALLEGRO_KEY_S))//if the key pressed was S then slow down animation
		{
			mSpeedGameDown = true;
		}

		else if (al_key_down(&mKeyBoardState, ALLEGRO_KEY_ENTER))//if the key pressed was enter then switch animations
		{
			if (mSwitchAnims == true)//if the switchAnims is currenting true, meaning if you can switch. set it to false. That way in my code, it will prevent the sprite from constantly swapping.
			{
				mSwitchAnims = false;
			}
			else//if the switch anim is false but enter was pressed, then yes we can swap animations.
				mSwitchAnims = true;
		}
		else
		{
			
		}
	}
}

void System::getMouseState()
{
	//get the state of the mouse
	al_get_mouse_state(&mMouseState);
	
	mMousePos.setX(mMouseState.x - 20.0f);//set the mouse position x with a displacement 
	mMousePos.setY(mMouseState.y - 20.0f);//set mouse position y with displacement

	//pass that state and if that state is left mouse down, then run
	if (al_mouse_button_down(&mMouseState,MOUSE_LEFT_CLICK))//if the key pressed was escape then close application
	{
		mCanMoveSprite = true;
	}
	else
	{
		mCanMoveSprite = false;
	}
}

void System::getMouseState(bool unitOnScreen)
{
	//get the state of the mouse
	al_get_mouse_state(&mMouseState);

	mMousePos.setX(mMouseState.x - 20.0f);//set the mouse position x with a displacement 
	mMousePos.setY(mMouseState.y - 20.0f);//set mouse position y with displacement

										  //pass that state and if that state is left mouse down, then run
	if (al_mouse_button_down(&mMouseState, MOUSE_LEFT_CLICK) && unitOnScreen == true)//if the key pressed was escape then close application
	{
		mCanMoveSprite = true;
	}
	else
	{
		mCanMoveSprite = false;
	}
}

bool System::getSpeedUpStatus()
{
	return mSpeedGameUp;
}

bool System::getSpeedDownStatus()
{
	return mSpeedGameDown;
}

bool System::getAnimationSwitchStatus()
{
	return mSwitchAnims;
}

GraphicsSystem * System::getGraphicSystem()
{
	return mpGraphicSys;
}