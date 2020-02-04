#include "InputTranslator.h"
#include "EventSystem.h"
//Input Events
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
//Game Events
#include "GameEvent.h"
#include "ExitGame.h"
#include "Options_Menu.h"
#include "Difficulty_Menu.h"
#include "Start_Game.h"
#include "Load_Game.h"
#include "Fire_Projectile.h"


InputTranslator::InputTranslator(EventSystem* pEventSystem) 
	:EventListener(pEventSystem)
{
	pEventSystem->addListener(SPACE, this);
	pEventSystem->addListener(O_KEY, this);
	pEventSystem->addListener(D_KEY, this);
	pEventSystem->addListener(L_KEY, this);
	pEventSystem->addListener(S_KEY, this);
	pEventSystem->addListener(ESCAPE, this);
	
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::init()
{

}

void InputTranslator::cleanup()
{

}

void InputTranslator::handleEvent(const Event& theEvent)
{

	if (theEvent.getType() == SPACE)
	{
		const KeyEvent& spaceKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = spaceKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(Fire_Projectile());
		}
	}
	else if (theEvent.getType() == O_KEY)
	{
		
		const KeyEvent& oKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = oKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(Options_Menu());
		}
		
		
	}
	else if (theEvent.getType() == D_KEY)
	{

		const KeyEvent& dKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = dKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(Difficulty_Menu());
		}


	}
	else if (theEvent.getType() == S_KEY)
	{

		const KeyEvent& sKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = sKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(Start_Game());
		}


	}
	else if (theEvent.getType() == L_KEY)
	{

		const KeyEvent& lKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = lKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(Load_Game());
		}


	}
	else if (theEvent.getType() == ESCAPE)
	{
		
		const KeyEvent& escapeKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = escapeKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(ExitGame());
		}

		
	}
	

}