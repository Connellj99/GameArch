#include "InputTranslator.h"
#include "Event.h"
#include "GameEvent.h"
#include "EventSystem.h"

InputTranslator::InputTranslator(EventSystem* eventSys) : EventListener(eventSys)
{
	eventSys->addListener(LEFT_CLICK, this);
	eventSys->addListener(RIGHT_CLICK, this);
	eventSys->addListener(SPACE_KEY, this);
	eventSys->addListener(ESC_KEY, this);
	eventSys->addListener(ENTER_KEY, this);
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::calledEvent(const Event &event)
{
	if(event.getType() == LEFT_CLICK)
	{
		getEventSystem()->fireEvent((EventType)CREATE);
	}
	else if(event.getType() == RIGHT_CLICK)
	{
		getEventSystem()->fireEvent((EventType)DEL);
	}
	else if(event.getType() == SPACE_KEY)
	{
		getEventSystem()->fireEvent((EventType)PAUSE);
	}
	else if(event.getType() == ESC_KEY)
	{
		getEventSystem()->fireEvent((EventType)EXIT);
	}
	else if(event.getType() == ENTER_KEY)
	{
		getEventSystem()->fireEvent((EventType)SWAP);
	}
}
