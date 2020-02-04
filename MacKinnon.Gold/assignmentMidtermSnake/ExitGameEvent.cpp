#include "ExitGameEvent.h"



ExitGameEvent::ExitGameEvent() 
	: Event((EventType)GameEvents::EXIT_GAME_EVENT)
{
}


ExitGameEvent::~ExitGameEvent()
{
}
