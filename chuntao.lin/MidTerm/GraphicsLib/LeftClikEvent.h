#ifndef LEFT_CLICK_H
#define LEFT_CLICK_H

// include event and vector data.
#include "Event.h"
#include "Vector2Data.h"


class LeftClickEvent : public Event
{
public:

	// Constructors
	LeftClickEvent(const Vector2& position);

	// Accessors
	Vector2 getPosition() const { return mPos; };

private:

	// Vector2's
	Vector2 mPos;

};

#endif

