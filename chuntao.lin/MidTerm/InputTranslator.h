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
#include "ToggleAnimations.h"
#include "FlipAnimations.h"

//Headers for game status
#include "Exit.h"
#include "StartGame.h"
#include "RestartEvent.h"

//Headers for movement/arrow key input
#include "MoveLeftEvent.h"
#include "MoveRightEvent.h"
#include "MoveUpEvent.h"
#include "MoveDownEvent.h"

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