#ifndef MOUSEMOVED_H
#define MOUSEMOVED_H

// Local includes
#include "Event.h"
#include "Vector2.h"


class MouseMovedEvent : public Event
{
public:

	// Constructors
	MouseMovedEvent(const Vector2& loc);

	// Accessors
	Vector2 getLocation() const { return mLoc; };

private:

	// Vector2's
	Vector2 mLoc;

};

#endif // !MOUSEMOVED_H

