#include "InputTranslator.h"
#include "EventSystem.h"
#include "Event.h"
#include "ClickEvent.h"
#include "KeyEvent.h"
#include "GameEvent.h"

int InputTranslator::msID = NULL;

InputTranslator::InputTranslator(EventSystem * pEventSystem)
	:EventListener(pEventSystem)
	,mID(msID)
{
	msID++;
	pEventSystem->addListener(CLICK_EVENT, this);
	pEventSystem->addListener(KEY_EVENT, this);
}

InputTranslator::~InputTranslator()
{}

void InputTranslator::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == CLICK_EVENT)
	{
		const ClickEvent& clickEvent = static_cast<const ClickEvent&>(theEvent);
		const Mouse& temp = clickEvent.getMouseCode();

		if (temp.leftDown)
		{
			EventSystem::getInstance()->fireEvent(UnitEvent(temp.position));
		}
		else if (temp.rightDown)
		{
			EventSystem::getInstance()->fireEvent(DestroyEvent(temp.position));
		}
	}
	else if(theEvent.getType() == KEY_EVENT)
	{
		const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);
		const Key& temp = keyEvent.getKeyCode();


		if (temp.enterDown)
		{
			EventSystem::getInstance()->fireEvent(Event((EventType)SWAP_ANIMATIONS));
		}
		else if (temp.escapeDown)
		{
			EventSystem::getInstance()->fireEvent(Event((EventType)EXIT_GAME));
		}
		else if (temp.spaceDown)
		{
			EventSystem::getInstance()->fireEvent(Event((EventType)PAUSE_ANIMATIONS));
		}
	}
}

