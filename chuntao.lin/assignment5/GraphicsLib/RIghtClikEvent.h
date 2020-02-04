#ifndef RIGHT_CLICK_H
#define RIGHT_CLICK_H

// Local includes
#include "Event.h"
#include "Vector2Data.h"

class RightClickEvent : public Event
{
public:

	// Constructors
	RightClickEvent(const Vector2& position);

	// Accessors
	Vector2 getPosition() const { return mPos; };

private:

	// Vector2's
	Vector2 mPos;
};

#endif

