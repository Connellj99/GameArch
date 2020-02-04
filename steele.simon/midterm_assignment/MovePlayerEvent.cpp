#include "MovePlayerEvent.h"

// This is the default constructor for the class
MovePlayerEvent::MovePlayerEvent(const Vector2& loc)
	:Event(EventType(MOVE_PLAYER))
	, mLoc(loc)
{
}