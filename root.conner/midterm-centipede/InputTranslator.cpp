/*
Conner Root
EGP 310-01
*/

#include "System.h"
#include "InputTranslator.h"
#include "EventSystem.h"
#include "MouseClickEvent.h"
#include "MouseMoveEvent.h"
#include "MovePlayerEvent.h"
#include "KeyDownEvent.h"
#include "GameEvent.h"
#include "SpawnEvent.h"
#include "DeleteEvent.h"
#include "ExitEvent.h"
#include "ChangeSpeedEvent.h"
#include "PauseEvent.h"
#include "ToggleAnimationEvent.h"

// Constructor
InputTranslator::InputTranslator()
{
}

// Init
void InputTranslator::init()
{
	EventSystem::getInstance()->addListener(MOUSE_CLICK_EVENT, this);
	EventSystem::getInstance()->addListener(MOUSE_MOVE_EVENT, this);
	EventSystem::getInstance()->addListener(KEY_DOWN_EVENT, this);
}

// Handle event
void InputTranslator::handleEvent(const Event &evt)
{
	if (evt.getType() == MOUSE_CLICK_EVENT)
	{
		MouseClickEvent clickEvt = dynamic_cast<const MouseClickEvent&>(evt);
		if (clickEvt.getMouseButtonDown() == 1)
			EventSystem::getInstance()->fireEvent(SpawnEvent(clickEvt.getXPos(), clickEvt.getYPos()));
		else if(clickEvt.getMouseButtonDown() == 2)
			EventSystem::getInstance()->fireEvent(DeleteEvent(clickEvt.getXPos(), clickEvt.getYPos()));
	}
	else if (evt.getType() == MOUSE_MOVE_EVENT)
	{
		MouseMoveEvent moveEvt = dynamic_cast<const MouseMoveEvent&>(evt);
		EventSystem::getInstance()->fireEvent(MovePlayerEvent(moveEvt.getXPos(), moveEvt.getYPos()));
	}
	else if (evt.getType() == KEY_DOWN_EVENT)
	{
		KeyDownEvent keyEvt = dynamic_cast<const KeyDownEvent&>(evt);
		auto keyCode = keyEvt.getKeyCode();
		switch (keyCode)
		{
		case ESC:
			EventSystem::getInstance()->fireEvent(ExitEvent());
			break;
		case F:
			EventSystem::getInstance()->fireEvent(ChangeSpeedEvent(1));
			break;
		case S:
			EventSystem::getInstance()->fireEvent(ChangeSpeedEvent(-1));
			break;
		case SPACE:
			EventSystem::getInstance()->fireEvent(PauseEvent());
			break;
		case ENTER:
			EventSystem::getInstance()->fireEvent(ToggleAnimationEvent());
			break;
		default:
			break;
		}
	}
}

// Destructor
InputTranslator::~InputTranslator()
{
}