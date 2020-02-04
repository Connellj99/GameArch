#ifndef INPUT_TRANSLATOR_H
#define INPUT_TRANSLATOR_H

#include "EventListener.h"

class InputTranslator : public EventListener
{
public:
	InputTranslator() {};
	~InputTranslator() {}

	void init();
	void update(float curTime);
private:
	void handleEvent(const Event& theEvent) override;

	EventSystem* pEventSystem = nullptr;
	bool mMouse1IsDown = false;
};
#endif