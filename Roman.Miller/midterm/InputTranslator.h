#pragma once
#include <Trackable.h>
#include "EventListener.h"
#include "InputSystem.h"
using namespace std;

class EventSystem;


class InputTranslator : public EventListener
{
public:
	InputTranslator(EventSystem* pEventSystem);
	~InputTranslator();

	void handleEvent(const Event& theEvent);

private:
	Key mLastFrameKey;
	int mID;
	static int msID;
};