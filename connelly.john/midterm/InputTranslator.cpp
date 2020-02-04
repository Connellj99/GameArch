#include "InputTranslator.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "InitSmurfEvent.h"
#include "MouseDownEvent.h"
#include "DestroySmurfEvent.h"
#include "KeyDownEvent.h"

InputTranslator::InputTranslator()
{
}

InputTranslator::~InputTranslator()
{
}

void InputTranslator::init()
{
	EventSystem::getInstance()->addListener(MOUSE_DOWN_EVENT, this);
	EventSystem::getInstance()->addListener(KEY_DOWN_EVENT, this);
}

void InputTranslator::handleEvent(const Event& theEvent)
{
	auto eventSystem = EventSystem::getInstance();

	switch (theEvent.getType())
	{
	case MOUSE_DOWN_EVENT:
	{
		auto mouseDownEvent = dynamic_cast<const MouseDownEvent&>(theEvent);
		const auto mouseButton = mouseDownEvent.getMouseButton();
		if (mouseButton == 1)
		{
			eventSystem->fireEvent(InitSmurfEvent(mouseDownEvent.getLoc()));
		}
		else if (mouseButton == 2)
		{
			eventSystem->fireEvent(DestroySmurfEvent(mouseDownEvent.getLoc()));
		}
		break;
	}
	case KEY_DOWN_EVENT:
	{
		auto keyDownEvent = dynamic_cast<const KeyDownEvent&>(theEvent);
		const auto keyCode = keyDownEvent.getKeyCode();
		if (keyCode == ENTER)
		{
			eventSystem->fireEvent(Event(EventType(SWAP_SMURF_ANIMATION_EVENT)));
		}
		else if(keyCode == SPACE)
		{
			eventSystem->fireEvent(Event(EventType(TOGGLE_SMURF_ANIMATIONS_EVENT)));
		}
		else if(keyCode == ESC)
		{
			eventSystem->fireEvent(Event(EventType(EXIT_GAME_EVENT)));
		}
		else if (keyCode == LEFT)
		{
			eventSystem->fireEvent(Event(EventType(MOVELEFT)));
		}
		else if (keyCode == RIGHT)
		{
			eventSystem->fireEvent(Event(EventType(MOVERIGHT)));
		}
		else if (keyCode == UP)
		{
			eventSystem->fireEvent(Event(EventType(MOVEUP)));
		}
		else if (keyCode == DOWN)
		{
			eventSystem->fireEvent(Event(EventType(MOVEDOWN)));
		}
		else if (keyCode == B)
		{
			eventSystem->fireEvent(Event(EventType(CREATE_WALL)));
		}
		else if (keyCode == FOOD)
		{
			eventSystem->fireEvent(Event(EventType(CREATE_FOOD)));
		}

		break;
	}
	default:;
	}
}
