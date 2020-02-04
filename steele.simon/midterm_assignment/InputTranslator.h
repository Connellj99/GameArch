#ifndef INPUTTRANSLATOR_H
#define INPUTTRANSLATOR_H

// Graphics-lib includes
#include <Vector2.h>
#include <LeftClickEvent.h>
#include <RightClickEvent.h>
#include <MouseMovedEvent.h>
#include <EventListener.h>
#include <EventSystem.h>

// Local includes
#include "GameEvent.h"
#include "SwitchAnimationEvent.h"
#include "QuitEvent.h"
#include "StopStartAnimationEvent.h"
#include "PlaceUnitEvent.h"
#include "DestroyUnitEvent.h"
#include "MovePlayerEvent.h"
#include "ShootEvent.h"
#include "StartGameEvent.h"


class InputTranslator : public EventListener
{
public:

	// Constructors
	InputTranslator(EventSystem* pEventSystem);

	// Destructors
	~InputTranslator();

	// Mutators
	void handleEvent(const Event& theEvent);

private:

};

#endif // !INPUTTRANSLATOR_H

