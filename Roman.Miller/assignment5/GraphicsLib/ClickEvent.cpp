#include "ClickEvent.h"

ClickEvent::ClickEvent(const Mouse & mouse)
	:Event(CLICK_EVENT)
	, mMouse(mouse)
{
}

ClickEvent::~ClickEvent()
{
}
