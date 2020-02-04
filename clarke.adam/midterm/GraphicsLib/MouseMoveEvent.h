#ifndef MOUSE_MOVE_EVENT_H
#define MOUSE_MOVE_EVENT_H

#include "Event.h"
#include "Vector2D.h"

class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(const Vector2D& loc, float curTime) : Event(MOUSE_MOVE_EVENT),
		mLoc(loc), mCurTime(curTime) {}

	Vector2D getLoc() const { return mLoc; }
	float getCurTime() const { return mCurTime; }
private:
	Vector2D mLoc;
	float mCurTime;
};
#endif