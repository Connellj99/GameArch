#include "ButtonPressEvent.h"

ButtonPressEvent::ButtonPressEvent(keys k) : Event(BUTTON_PRESS_EVENT)
{
	mKey = k;
}

ButtonPressEvent::~ButtonPressEvent()
{

}