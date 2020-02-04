#include "AddEvent.h"

AddEvent::AddEvent(float xLoc, float yLoc) : Event(ADD_EVENT)
{
	x = xLoc;
	y = yLoc;
}

AddEvent::~AddEvent()
{

}