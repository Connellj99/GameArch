#include "ChangeDirectionEvent.h"



ChangeDirectionEvent::ChangeDirectionEvent(int x, int y) 
	: Event((EventType)GameEvents::CHANGE_DIRECTION_EVENT)
{
	mXValue = x;
	mYValue = y;

}


ChangeDirectionEvent::~ChangeDirectionEvent()
{
}
