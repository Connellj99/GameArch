#include "MouseMovedEvent.h"

MouseMovedEvent::MouseMovedEvent(const Vector2& loc)
	:Event(MOUSE_CURSOR_MOVED)
	, mLoc(loc)
{
}