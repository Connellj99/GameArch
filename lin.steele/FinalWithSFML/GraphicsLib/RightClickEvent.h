#ifndef RIGHTCLICKEVENT_H
#define RIGHTCLICKEVENT_H

// Local includes
#include "Event.h"
#include "Vector2.h"


class RightClickPressedEvent : public Event
{
public:

	// Constructors
	RightClickPressedEvent(const Vector2& loc);

	// Accessors
	Vector2 getLocation() const { return mLoc; };

private:

	// Vector2's
	Vector2 mLoc;

};

#endif // !RIGHTCLICKEVENT_H

