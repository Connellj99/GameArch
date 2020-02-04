#include "InputTranslator.h"

InputTranslator::InputTranslator()
{
	
}

InputTranslator::InputTranslator(EventSystem* passedEventSystem) :EventListener(passedEventSystem)
{
	//add listeners to the mouse inputs
	passedEventSystem->addListener(LEFT_CLICK_PRESSED, this);
	passedEventSystem->addListener(RIGHT_CLICK_PRESSED, this);
	//add listeners to the key inputs
	passedEventSystem->addListener(ENTER_BUTTON_RELEASED, this);
	passedEventSystem->addListener(ESCAPE_BUTTON_RELEASED, this);
	passedEventSystem->addListener(SPACE_BUTTON_RELEASED, this);
	passedEventSystem->addListener(R_BUTTON_RELEASED, this);
	//add listeners to the arrow key inputs
	passedEventSystem->addListener(LEFT_ARROW_RELEASED, this);
	passedEventSystem->addListener(RIGHT_ARROW_RELEASED, this);
	passedEventSystem->addListener(UP_ARROW_RELEASED, this);
	passedEventSystem->addListener(DOWN_ARROW_RELEASED, this);
}

InputTranslator::~InputTranslator()
{
	
}

void InputTranslator::handleEvent(const Event &chosenEvent)
{
	//Handle Events for Keyboard input
	if (chosenEvent.getType() == SPACE_BUTTON_RELEASED)//if the passed in event type matches the space, then fire an event using the Toggle animation event class
	{
		//mpGetEventSystem()->fireEvent(ToggleAnimEvent());
		mpGetEventSystem()->fireEvent(StartEvent());
	}

	if (chosenEvent.getType() == ESCAPE_BUTTON_RELEASED)//if the passed in event type matches the Escape, then fire an event using the Exit event class
	{
		mpGetEventSystem()->fireEvent(ExitEvent());
	}

	if (chosenEvent.getType() == ENTER_BUTTON_RELEASED)//if the passed in event type matches the enter, then fire an event using the Flip animation event class
	{
		//mpGetEventSystem()->fireEvent(FlipAnimEvent());
		/*mpGetEventSystem()->fireEvent(StartEvent());*/
	}

	if (chosenEvent.getType() == R_BUTTON_RELEASED)//if the passed in event type matches the R, then fire an event using the restart event class
	{
		mpGetEventSystem()->fireEvent(RestartEvent());
	}

	//Handle Eventsn for arrow key input
	if (chosenEvent.getType() == LEFT_ARROW_RELEASED)
	{
		mpGetEventSystem()->fireEvent(MoveLeftEvent());
	}

	if (chosenEvent.getType() == RIGHT_ARROW_RELEASED)
	{
		mpGetEventSystem()->fireEvent(MoveRightEvent());
	}

	if (chosenEvent.getType() == UP_ARROW_RELEASED)
	{
		mpGetEventSystem()->fireEvent(MoveUpEvent());
	}

	if (chosenEvent.getType() == DOWN_ARROW_RELEASED)
	{
		mpGetEventSystem()->fireEvent(MoveDownEvent());
	}

	//Hande Events for Mouse Inputs
	if (chosenEvent.getType() == LEFT_CLICK_PRESSED)//if the passed in event type matches the left click, then fire an event using the Create unit event class
	{
		const LeftClickEvent& leftEvent = static_cast<const LeftClickEvent&>(chosenEvent);
		//mpGetEventSystem()->fireEvent(CreateUnit(leftEvent.getPosition()));
	}

	if (chosenEvent.getType() == RIGHT_CLICK_PRESSED)//if the passed in event type matches the right click, then fire an event using the Delete unit event class
	{
		const RightClickEvent& rightEvent = static_cast<const RightClickEvent&>(chosenEvent);
		//mpGetEventSystem()->fireEvent(DeleteUnit(rightEvent.getPosition()));
	}
}