#ifndef MOUSE_DOWN_EVENT_H
#define MOUSE_DOWN_EVENT_H

#include "Event.h"
#include "Vector2D.h"

class MouseDownEvent : public Event
{
public:
	MouseDownEvent(int mouseButton, const Vector2D& loc) : Event(MOUSE_DOWN_EVENT),
	mMouseButton(mouseButton), mLoc(loc) {}

	int getMouseButton() const { return mMouseButton; }
	Vector2D getLoc() const { return mLoc; }
private:
	int mMouseButton;
	Vector2D mLoc;
};
#endif