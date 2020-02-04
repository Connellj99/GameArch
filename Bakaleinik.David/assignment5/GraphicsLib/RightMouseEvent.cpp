#include "RightMouseEvent.h"

RightMouseEvent::RightMouseEvent(int x, int y)
	:Event(RIGHT_MOUSE_BUTTON)
{
	mX = x;
	mY = y;
}

RightMouseEvent::~RightMouseEvent()
{

}