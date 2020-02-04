#include "InputTranslator.h"
#include "Header.h"
#include "Event.h"
#include "MousePressEvent.h"
#include "ButtonPressEvent.h"
#include "Game.h"
#include "AddEvent.h"
#include "DeleteEvent.h"
#include "ExitEvent.h"
#include "FreezeEvent.h"
#include "DeanEvent.h"

InputTranslator::InputTranslator(EventSystem* pESys) : EventListener(pESys)
{
	pGame->getInstance()->addListener(MOUSE_PRESS_EVENT, this);
	pGame->getInstance()->addListener(BUTTON_PRESS_EVENT, this);
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::handleEvent(const Event& ev)
{

	if (ev.getType() == MOUSE_PRESS_EVENT)
	{
		const MousePressEvent& temp = static_cast<const MousePressEvent&>(ev);
		if (temp.getState() == 1)
		{
			pGame->getInstance()->fireEvent(AddEvent(temp.getX(), temp.getY()));
		}
		else if (temp.getState() == 2)
		{
			pGame->getInstance()->fireEvent(DeleteEvent(temp.getX(), temp.getY()));
		}
		
	}
	else if (ev.getType() == BUTTON_PRESS_EVENT)
	{
		const ButtonPressEvent &temp = static_cast<const ButtonPressEvent&>(ev);
		if (temp.getKey() == ESCAPE_KEY)
		{
			pGame->getInstance()->fireEvent(ExitEvent());
		}
		else if (temp.getKey() == SPACE_KEY)
		{
			pGame->getInstance()->fireEvent(FreezeEvent());
		}
		else if (temp.getKey() == ENTER_KEY)
		{
			pGame->getInstance()->fireEvent(DeanEvent());
		}
	}
	/*else if (ev.getType() == EXIT_EVENT)
	{
		pGame->getInstance()->shouldExit();
	}
	else if (ev.getType() == FREEZE_EVENT)
	{
		const FreezeEvent &temp = static_cast<const FreezeEvent&>(ev);
		pGame->getInstance()->enableUnitUpdating(temp.shouldFreeze());
	}*/
	else
	{
		std::cout << "EVENT TYPE NOT IDENTIFIED" << std::endl;
	}
}