#include "LeftClickEvent.h"


// This is the default constructor for this class
LeftClickPressedEvent::LeftClickPressedEvent(const Vector2& loc)
	:Event(LEFT_MOUSE_PRESSED)
	, mLoc(loc)
{
}