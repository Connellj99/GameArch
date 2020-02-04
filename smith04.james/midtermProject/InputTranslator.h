#pragma once

#include "EventListener.h"

class InputTranslator : public EventListener
{
public:
	InputTranslator(EventSystem* pESys);
	~InputTranslator();

	void handleEvent(const Event& ev);
};