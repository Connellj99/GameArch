/*
Conner Root
EGP 310-01
*/

#pragma once

#include "EventListener.h"

class InputTranslator : public EventListener
{
private:

public:
	// Constructor
	InputTranslator();

	// Init/Cleanup
	void init();

	// Handle event
	void handleEvent(const Event&) override;
	
	// Destructor
	~InputTranslator();
};