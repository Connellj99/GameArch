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
	mLastFrameKey = Key();
}

InputTranslator::~InputTranslator()
{}

void InputTranslator::handleEvent(const Event & theEvent)
{
	if(theEvent.getType() == KEY_EVENT)
	{
		const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);
		const Key& temp = keyEvent.getKeyCode();


		if (temp.escapeDown)
		{
			EventSystem::getInstance()->fireEvent(Event((EventType)EXIT_GAME));
		}
		else if (temp.spaceDown)
		{
			if(!mLastFrameKey.spaceDown)
			EventSystem::getInstance()->fireEvent(Event((EventType)START));
		}
		else if (temp.aDown)
		{
			if(!mLastFrameKey.aDown)
				EventSystem::getInstance()->fireEvent(Event((EventType)LEFT));
		}
		else if(temp.sDown)
		{
			if(!mLastFrameKey.sDown)
			EventSystem::getInstance()->fireEvent(Event((EventType)DOWN));
		}
		else if(temp.wDown)
		{
			if(!mLastFrameKey.wDown)
			EventSystem::getInstance()->fireEvent(Event((EventType)UP));
		}
		else if (temp.dDown)
		{
			if(!mLastFrameKey.dDown)
			EventSystem::getInstance()->fireEvent(Event((EventType)RIGHT));
		}
		else if (temp.left)
		{
			if (!mLastFrameKey.left)
				EventSystem::getInstance()->fireEvent(Event((EventType)LEFT));
		}
		else if (temp.right)
		{
			if (!mLastFrameKey.right)
				EventSystem::getInstance()->fireEvent(Event((EventType)RIGHT));
		}
		else if (temp.down)
		{
			if (!mLastFrameKey.down)
				EventSystem::getInstance()->fireEvent(Event((EventType)DOWN));
		}
		else if (temp.up)
		{
			if (!mLastFrameKey.up)
				EventSystem::getInstance()->fireEvent(Event((EventType)UP));
		}

		mLastFrameKey = temp;
	}
}

