#ifndef LEFTCLICKEVENT_H
#define LEFTCLICKEVENT_H

// Local includes
#include "Event.h"
#include "Vector2.h"


class LeftClickPressedEvent : public Event
{
public:

	// Constructors
	LeftClickPressedEvent(const Vector2& loc);

	// Accessors
	Vector2 getLocation() const { return mLoc; };

private:

	// Vector2's
	Vector2 mLoc;

};

#endif // !LEFTCLICKEVENT_H

