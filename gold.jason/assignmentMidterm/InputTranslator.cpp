#include "InputTranslator.h"
#include "Event.h"
#include "GameEvent.h"
#include "EventSystem.h"

InputTranslator::InputTranslator(EventSystem* eventSys) : EventListener(eventSys)
{
	eventSys->addListener(LEFT_KEY, this);
	eventSys->addListener(RIGHT_KEY, this);
	eventSys->addListener(UP_KEY, this);
	eventSys->addListener(DOWN_KEY, this);
	eventSys->addListener(ESC_KEY, this);
	eventSys->addListener(R_KEY, this);
	eventSys->addListener(SPACE_KEY, this);
	eventSys->addListener(N_KEY, this);
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::calledEvent(const Event &event)
{
	if(event.getType() == LEFT_KEY)
	{
		getEventSystem()->fireEvent((EventType)LEFT);
	}
	else if(event.getType() == RIGHT_KEY)
	{
		getEventSystem()->fireEvent((EventType)RIGHT);
	}
	else if(event.getType() == UP_KEY)
	{
		getEventSystem()->fireEvent((EventType)UP);
	}
	else if(event.getType() == DOWN_KEY)
	{
		getEventSystem()->fireEvent((EventType)DOWN);
	}
	else if(event.getType() == ESC_KEY)
	{
		getEventSystem()->fireEvent((EventType)ESC_KEY);
	}
}
