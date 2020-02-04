#pragma once
#include <Trackable.h>
#include "EventListener.h"
using namespace std;

class EventSystem;

class InputTranslator : public EventListener
{
public:
	InputTranslator(EventSystem* pEventSystem);
	~InputTranslator();

	void handleEvent(const Event& theEvent);

private:
	int mID;
	static int msID;
};