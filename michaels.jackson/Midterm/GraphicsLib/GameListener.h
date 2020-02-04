#pragma once
#include "EventListener.h"

class GameListener : public EventListener
{
	GameListener(EventSystem* pEventSystem);
	~GameListener();

	void handleEvent(const Event& theEvent);

private:
	static int msID;

	int mID;
};