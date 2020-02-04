/*The class which responds to any events triggered by the InputSystem. It will translate the events into
Game Events which will be dispatched using a Game specific Event System.
Data
• Any data necessary to fulfill the requirements of the assignment
Public Functions
• Init/Cleanup/Constructor/Destructor*/

#pragma once


#include "EventListener.h"

class InputTranslator : public EventListener
{
public:
	InputTranslator();
	~InputTranslator();

	void init();

private:
	void handleEvent(const Event& theEvent) override;
};
