#include "DeleteEvent.h"

DeleteEvent::DeleteEvent(float xLoc, float yLoc) : Event(DELETE_EVENT)
{
	x = xLoc;
	y = yLoc;
}

DeleteEvent::~DeleteEvent()
{

}