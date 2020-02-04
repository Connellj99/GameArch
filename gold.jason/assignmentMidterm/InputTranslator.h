#ifndef InputTranslator_h
#define InputTranslator_h
#include "EventListener.h"
#include "EventSystem.h"

class InputTranslator : public EventListener
{
public:
	InputTranslator(EventSystem* eventSys);
	~InputTranslator();

	void calledEvent(const Event &event);
};
#endif // !InputTranslator_h