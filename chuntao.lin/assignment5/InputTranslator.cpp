#include "InputTranslator.h"

InputTranslator::InputTranslator()
{
	
}

InputTranslator::InputTranslator(EventSystem* passedEventSystem) :EventListener(passedEventSystem)
{
	passedEventSystem->addListener(LEFT_CLICK_PRESSED, this);
	passedEventSystem->addListener(RIGHT_CLICK_PRESSED, this);
	passedEventSystem->addListener(ENTER_BUTTON_RELEASED, this);
	passedEventSystem->addListener(ESCAPE_BUTTON_RELEASED, this);
	passedEventSystem->addListener(SPACE_BUTTON_RELEASED, this);
}

InputTranslator::~InputTranslator()
{
	
}

void InputTranslator::handleEvent(const Event &chosenEvent)
{
	if (chosenEvent.getType() == SPACE_BUTTON_RELEASED)//if the passed in event type matches the space, then fire an event using the Toggle animation event class
	{
		mpGetEventSystem()->fireEvent(ToggleAnimEvent());
	}

	if (chosenEvent.getType() == ESCAPE_BUTTON_RELEASED)//if the passed in event type matches the Escape, then fire an event using the Exit event class
	{
		mpGetEventSystem()->fireEvent(ExitEvent());
	}

	if (chosenEvent.getType() == ENTER_BUTTON_RELEASED)//if the passed in event type matches the enter, then fire an event using the Flip animation event class
	{
		mpGetEventSystem()->fireEvent(FlipAnimEvent());
	}

	if (chosenEvent.getType() == LEFT_CLICK_PRESSED)//if the passed in event type matches the left click, then fire an event using the Create unit event class
	{
		const LeftClickEvent& leftEvent = static_cast<const LeftClickEvent&>(chosenEvent);
		mpGetEventSystem()->fireEvent(CreateUnit(leftEvent.getPosition()));
	}

	if (chosenEvent.getType() == RIGHT_CLICK_PRESSED)//if the passed in event type matches the right click, then fire an event using the Delete unit event class
	{
		const RightClickEvent& rightEvent = static_cast<const RightClickEvent&>(chosenEvent);
		mpGetEventSystem()->fireEvent(DeleteUnit(rightEvent.getPosition()));
	}
}