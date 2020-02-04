#pragma once
#include "Event.h"
#include "Vector2D.h"
#include "InputSystem.h"

class ClickEvent : public Event
{
public:
	ClickEvent(const Mouse& mouse);
	~ClickEvent();

	Mouse getMouseCode() const { return mMouse; };

private:
	Mouse mMouse;
};