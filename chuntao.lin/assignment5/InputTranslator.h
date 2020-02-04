#ifndef INPUT_TRANSLATOR_H
#define INPUT_TRANSLATOR_H

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

//Headers for event related info
#include "EventListener.h"
#include "EventSystem.h"

//for position of mouse and functionality
#include "LeftClikEvent.h"
#include "RIghtClikEvent.h"

//Headers for the unit create, delete, animations and quitting game.
#include "CreateUnitEvent.h"
#include "DeleteUnitEvent.h"
#include "Exit.h"
#include "ToggleAnimations.h"
#include "FlipAnimations.h"

using namespace std;

class InputTranslator : public EventListener
{
public:
	InputTranslator();
	InputTranslator(EventSystem* passedEventSystem);
		
	~InputTranslator();

	void handleEvent(const Event& chosenEvent);

private:
	
};
#endif