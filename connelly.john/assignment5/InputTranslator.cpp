/*The class which responds to any events triggered by the InputSystem. It will translate the events into
Game Events which will be dispatched using a Game specific Event System.
Data
• Any data necessary to fulfill the requirements of the assignment
Public Functions
• Init/Cleanup/Constructor/Destructor*/

#include "InputTranslator.h"
#include "EventSystem.h"


void InputTranslator::init()
{
	EventSystem::getInstance()->addListener(MOUSE_DOWN_EVENT, this);
	EventSystem::getInstance()->addListener(KEY_DOWN_EVENT, this);
}