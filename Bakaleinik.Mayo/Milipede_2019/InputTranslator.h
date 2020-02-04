#pragma once
#include "Trackable.h"
#include "EventListener.h"

class EventSystem;

class InputTranslator : public EventListener
{
private:


public:

	InputTranslator(EventSystem* pEventSystem);
	//InputTranslator();
	~InputTranslator();

	void handleEvent(const Event& event);
	void init();
	void cleanup();
};