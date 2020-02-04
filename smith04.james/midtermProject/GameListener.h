#pragma once

#include "EventListener.h"

class GameListener : public EventListener
{
public:
	GameListener(EventSystem* pESys);
	~GameListener();

	void handleEvent(const Event& theEvent);
};