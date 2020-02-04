#include "MouseEvent.h"

MouseEvent::MouseEvent(const Vector2D& loc, const MouseButtonType& mb)
	: Event(MOUSE_CHANGED), mLoc(loc), mbType(mb)
{
}

MouseEvent::~MouseEvent()
{
}