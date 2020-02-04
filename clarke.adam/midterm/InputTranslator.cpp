#include "InputTranslator.h"
#include "GameEvent.h"
#include "EventSystem.h"
#include "KeyDownEvent.h"
#include "MouseMoveEvent.h"
#include "PlayerMoveEvent.h"
#include "MouseClickEvent.h"

void InputTranslator::init()
{
	pEventSystem = EventSystem::getInstance();
	pEventSystem->addListener(MOUSE_CLICK_EVENT, this);
	pEventSystem->addListener(KEY_DOWN_EVENT, this);
	pEventSystem->addListener(MOUSE_MOVE_EVENT, this);
}

void InputTranslator::update(float curTime)
{
	if (mMouse1IsDown)
	{
		pEventSystem->fireEvent(Event(EventType(PLAYER_SHOOT_EVENT)));
	}
}

void InputTranslator::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case MOUSE_CLICK_EVENT:
	{
		auto mouseEvent = dynamic_cast<const MouseClickEvent&>(theEvent);
		const auto mouseButton = mouseEvent.getMouseButton();
		if (mouseButton == 1)
		{
			mMouse1IsDown = mouseEvent.getIsDown();
		}
		break;
	}
	case KEY_DOWN_EVENT:
	{
		auto keyDownEvent = dynamic_cast<const KeyDownEvent&>(theEvent);
		const auto keyCode = keyDownEvent.getKeyCode();
		if (keyCode == SPACE)
		{
			pEventSystem->fireEvent(Event(EventType(PLAY_EVENT)));
		}
		else if (keyCode == ESC)
		{
			pEventSystem->fireEvent(Event(EventType(EXIT_GAME_EVENT)));
		}
		break;
	}
	case MOUSE_MOVE_EVENT:
	{
		auto mouseMoveEvent = dynamic_cast<const MouseMoveEvent&>(theEvent);
		pEventSystem->fireEvent(PlayerMoveEvent(mouseMoveEvent.getLoc(), mouseMoveEvent.getCurTime()));
		break;
	}
	default:;
	}
}
