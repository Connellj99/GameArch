#include "RightClickEvent.h"


// This is the default constructor for this class
RightClickPressedEvent::RightClickPressedEvent(const Vector2& loc)
	:Event(RIGHT_MOUSE_PRESSED)
	, mLoc(loc)
{
}