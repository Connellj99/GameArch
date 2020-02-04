#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

// Local Graphics-lib includes
#include "EventSystem.h"
#include "Event.h"
#include "LeftClickEvent.h"
#include "RightClickEvent.h"
#include "Vector2.h"
#include "System.h"

class InputSystem
{
public:
	// Constructors
	InputSystem();

	// Destructors
	~InputSystem();

	// Initializers / Cleanuppers
	void init();
	void cleanup();

	// Update functions
	void update();

private:
	
	// Booleans
	bool mIsSpaceDown;
	bool mIsEscapeDown;
	bool mIsEnterDown;

};

#endif // !INPUTSYSTEM_H

