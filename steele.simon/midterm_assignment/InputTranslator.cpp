#include "InputTranslator.h"

InputTranslator::InputTranslator(EventSystem* pEventSystem)
	:EventListener(pEventSystem)
{
	pEventSystem->addListener(ENTER_KEY_RELEASED, this);
	pEventSystem->addListener(ESCAPE_KEY_RELEASED, this);
	pEventSystem->addListener(SPACE_KEY_RELEASED, this);
	pEventSystem->addListener(LEFT_MOUSE_PRESSED, this);
	pEventSystem->addListener(RIGHT_MOUSE_PRESSED, this);
	pEventSystem->addListener(MOUSE_CURSOR_MOVED, this);
}

InputTranslator::~InputTranslator()
{
}

void InputTranslator::handleEvent(const Event &theEvent)
{
	if (theEvent.getType() == ENTER_KEY_RELEASED)
	{
		getEventSystem()->fireEvent(SwitchAnimationEvent());
	}
	if (theEvent.getType() == ESCAPE_KEY_RELEASED) 
	{
		getEventSystem()->fireEvent(QuitEvent());
	}
	if (theEvent.getType() == SPACE_KEY_RELEASED)
	{
		getEventSystem()->fireEvent(StartGameEvent());
	}
	if (theEvent.getType() == LEFT_MOUSE_PRESSED) 
	{
		getEventSystem()->fireEvent(ShootBulletEvent());
	}
	if (theEvent.getType() == RIGHT_MOUSE_PRESSED) 
	{
		const RightClickPressedEvent& moveEvent = static_cast<const RightClickPressedEvent&>(theEvent);
		getEventSystem()->fireEvent(DestroyUnitEvent(moveEvent.getLocation()));
	}
	if (theEvent.getType() == MOUSE_CURSOR_MOVED) 
	{
		const MouseMovedEvent& moveEvent = static_cast<const MouseMovedEvent&>(theEvent);
		getEventSystem()->fireEvent(MovePlayerEvent(moveEvent.getLocation()));
	}
}