#include "RightClikEvent.h"


// This is the default constructor for this class
RightClickEvent::RightClickEvent(const Vector2& position)
	:Event(RIGHT_CLICK_PRESSED)
	, mPos(position)
{
}