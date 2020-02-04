#include "InputTranslator.h"
#include "GameMouseEvent.h"
#include "GameKeyEvent.h"
#include "GamePowerupEvent.h"


int InputTranslator::msID = 0;

InputTranslator::InputTranslator()
{
}

InputTranslator::~InputTranslator()
{
}

InputTranslator::InputTranslator(EventSystem* pEventSystem)
	:EventListener(pEventSystem),
	mID(msID)
{
	msID++;
	pEventSystem->addListener(MOUSE_CHANGED, this);
	pEventSystem->addListener(KEY_CHANGED, this);
	pEventSystem->addListener(POWERUP_EATEN, this);
}

void InputTranslator::handleEvent(const Event& theEvent)
{
	
	switch (theEvent.getType())
	{
	case MOUSE_CHANGED:
		handleMouseEvent(theEvent);
		break;
	case KEY_CHANGED:
		handleKeyEvent(theEvent);
		break;
	case POWERUP_EATEN:
		handlePowerupEvent(theEvent);
	}
}

void InputTranslator::handleMouseEvent(const Event& theEvent)
{
	EventSystem* fireSystem = getEventSystem();
	const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
	fireSystem->fireEvent(GameMouseEvent(mouseEvent.getLocation(), mouseEvent.getButtonType()));
}

void InputTranslator::handleKeyEvent(const Event& theEvent)
{
	EventSystem* fireSystem = getEventSystem();
	const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);
	fireSystem->fireEvent(GameKeyEvent(keyEvent.getButtonType()));
}

void InputTranslator::handlePowerupEvent(const Event& theEvent)
{
	EventSystem* fireSystem = getEventSystem();
	const PowerupEvent& powerupEvent = static_cast<const PowerupEvent&>(theEvent);
	fireSystem->fireEvent(GamePowerupEvent(powerupEvent.getButtonType()));
}