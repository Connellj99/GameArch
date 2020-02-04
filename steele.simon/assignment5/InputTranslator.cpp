#include "InputTranslator.h"

InputTranslator::InputTranslator(EventSystem* pEventSystem)
	:EventListener(pEventSystem)
{
	pEventSystem->addListener(ENTER_KEY_RELEASED, this);
	pEventSystem->addListener(ESCAPE_KEY_RELEASED, this);
	pEventSystem->addListener(SPACE_KEY_RELEASED, this);
	pEventSystem->addListener(LEFT_MOUSE_PRESSED, this);
	pEventSystem->addListener(RIGHT_MOUSE_PRESSED, this);
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
		getEventSystem()->fireEvent(StopStartAnimationEvent());
	}
	if (theEvent.getType() == LEFT_MOUSE_PRESSED) 
	{
		const LeftClickPressedEvent& moveEvent = static_cast<const LeftClickPressedEvent&>(theEvent);
		getEventSystem()->fireEvent(PlaceUnitEvent(moveEvent.getLocation()));
	}
	if (theEvent.getType() == RIGHT_MOUSE_PRESSED) 
	{
		const RightClickPressedEvent& moveEvent = static_cast<const RightClickPressedEvent&>(theEvent);
		getEventSystem()->fireEvent(DestroyUnitEvent(moveEvent.getLocation()));
	}
}