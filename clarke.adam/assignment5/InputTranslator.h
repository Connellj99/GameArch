#ifndef INPUT_TRANSLATOR_H
#define INPUT_TRANSLATOR_H

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
#endif