#ifndef MOUSE_CLICK_EVENT_H
#define MOUSE_CLICK_EVENT_H

#include "Event.h"
#include "Vector2D.h"

class MouseClickEvent : public Event
{
public:
	MouseClickEvent(int mouseButton, bool isDown, const Vector2D& loc)
		: Event(MOUSE_CLICK_EVENT), mMouseButton(mouseButton), mIsDown(isDown), mLoc(loc) {}

	int getMouseButton() const { return mMouseButton; }
	bool getIsDown() const { return mIsDown; }
	Vector2D getLoc() const { return mLoc; }
private:
	int mMouseButton;
	bool mIsDown;
	Vector2D mLoc;
};
#endif