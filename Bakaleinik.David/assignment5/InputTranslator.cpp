#include "InputTranslator.h"
#include "EventSystem.h"
//Input Events
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
//Game Events
#include "GameEvent.h"
#include "CreateUnit.h"
#include "DeleteUnit.h"
#include "ExitGame.h"
#include "SwitchHead.h"
#include "StopAnim.h"


InputTranslator::InputTranslator(EventSystem* pEventSystem) 
	:EventListener(pEventSystem)
{
	pEventSystem->addListener(SPACE, this);
	pEventSystem->addListener(ENTER, this);
	pEventSystem->addListener(ESCAPE, this);
	pEventSystem->addListener(RIGHT_MOUSE_BUTTON, this);
	pEventSystem->addListener(LEFT_MOUSE_BUTTON, this);
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
			getEventSystem()->fireEvent(StopAnimation());
		}
	}
	else if (theEvent.getType() == ENTER)
	{
		
		const KeyEvent& enterKey = static_cast<const KeyEvent&>(theEvent);
		bool shouldFire = enterKey.getKeyStatus();

		if (shouldFire)
		{
			getEventSystem()->fireEvent(SwitchHead());
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
	else if (theEvent.getType() == LEFT_MOUSE_BUTTON)
	{
		const MouseEvent& leftMouse = static_cast<const MouseEvent&>(theEvent);
		getEventSystem()->fireEvent(CreateUnit(leftMouse.getX(), leftMouse.getY()));
	}
	else if (theEvent.getType() == RIGHT_MOUSE_BUTTON)
	{
		const MouseEvent& rightMouse = static_cast<const MouseEvent&>(theEvent);

		getEventSystem()->fireEvent(DeleteUnit(rightMouse.getX(), rightMouse.getY()));
	}

}