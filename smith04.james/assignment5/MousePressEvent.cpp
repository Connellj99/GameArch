#include "MousePressEvent.h"

MousePressEvent::MousePressEvent(int state, float xLoc, float yLoc) : Event(MOUSE_PRESS_EVENT)
{
	mState = state;
	x = xLoc;
	y = yLoc;
}

MousePressEvent::~MousePressEvent()
{

}