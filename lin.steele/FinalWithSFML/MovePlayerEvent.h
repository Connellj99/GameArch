#ifndef MOVEPLAYEREVENT_H
#define MOVEPLAYEREVENT_H

// Local includes
#include "GameEvent.h"

// Graphics-lib includes
#include <Vector2.h>


class MovePlayerEvent : public Event
{
public:

	// Constructors
	MovePlayerEvent(const Vector2& loc);

	// Accessors
	Vector2 getLocation() const { return mLoc; };

private:

	// Vector2's
	Vector2 mLoc;
};

#endif // !MOVEPLAYEREVENT_H

