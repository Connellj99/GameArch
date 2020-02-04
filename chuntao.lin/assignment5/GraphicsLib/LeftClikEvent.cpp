#include "LeftClikEvent.h"


// This is the default constructor for this class
LeftClickEvent::LeftClickEvent(const Vector2& position)
	:Event(LEFT_CLICK_PRESSED)
	, mPos(position)
{
}