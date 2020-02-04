#pragma once
#ifndef INPUT_TRANSLATOR_H
#define INPUT_TRANSLATOR_H

#include "EventSystem.h"
#include "EventListener.h"
#include <Trackable.h>

class InputTranslator :public EventListener
{
private:
	static int msID;
	int mID;

public:
	InputTranslator();
	InputTranslator::InputTranslator(EventSystem* pEventSystem);
	~InputTranslator();

	void handleEvent(const Event& theEvent);
	void handleMouseEvent(const Event& theEvent);
	void handleKeyEvent(const Event& theEvent);
	void handlePowerupEvent(const Event& theEvent);
	void handleBonusEvent(const Event& theEvent);

	int getID() { return mID; }

};

#endif