#include "LeftMouseEvent.h"

LeftMouseEvent::LeftMouseEvent(int x, int y)
	:Event(LEFT_MOUSE_BUTTON)
{
	mX = x;
	mY = y;
}

LeftMouseEvent::~LeftMouseEvent()
{

}