#include "InputTranslator.h"
#include "Event.h"
#include "EventSystem.h"
#include "MouseClickEvent.h"
#include "KeyPressEvent.h"
#include "CreateUnitEvent.h"
#include "DeleteUnitEvent.h"
#include "SwapAnimationEvent.h"
#include "ExitGameEvent.h"
#include "ToggleAnimationActiveEvent.h"

InputTranslator::InputTranslator()
{
}


InputTranslator::~InputTranslator()
{
	cleanup();
}

//adds lsiteneres for key presses and mouse presses to the instance of the event system
void InputTranslator::init()
{
	mIsInit = true;
	EventSystem::getInstance()->addListener(KEY_PRESS_EVENT, this);
	EventSystem::getInstance()->addListener(MOUSE_PRESS_EVENT, this);
}

void InputTranslator::cleanup()
{
	if (mIsInit) 
	{
		mIsInit = false;
	}
}

//receives the event and determines what action needs to occurr based on the input
void InputTranslator::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == KEY_PRESS_EVENT) 
	{
		const KeyPressEvent& keyEvent = static_cast<const KeyPressEvent&>(theEvent);

		switch (keyEvent.getPressedKey()) 
		{
		case ENTER_KEY:
		{
			EventSystem::getInstance()->fireEvent(SwapAnimationEvent());
			break;
		}
		case SPACE_KEY:
		{
			EventSystem::getInstance()->fireEvent(ToggleAnimationActiveEvent());
			break;
		}
		case ESCAPE_KEY:
		{
			EventSystem::getInstance()->fireEvent(ExitGameEvent());
			break;
		}
		}
	}
	if (theEvent.getType() == MOUSE_PRESS_EVENT) 
	{
		const MouseClickEvent& mouseEvent = static_cast<const MouseClickEvent&>(theEvent);

		switch (mouseEvent.getPressedbutton()) 
		{
		case 1:
		{
			EventSystem::getInstance()->fireEvent(CreateUnitEvent(mouseEvent.getMousePos()));
			break;
		}
		case 2:
		{
			EventSystem::getInstance()->fireEvent(DeleteUnitEvent(mouseEvent.getMousePos()));
			break;
		}
		}
	}
}
