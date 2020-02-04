#ifndef INIT_MUSHROOM_EVENT_H
#define INIT_MUSHROOM_EVENT_H

#include "Event.h"
#include "GameEvent.h"
#include "Vector2D.h"

class InitMushroomEvent : public Event
{
public:
	InitMushroomEvent(const Vector2D& initLoc) : Event(EventType(INIT_MUSHROOM_EVENT)),
		mInitLoc(initLoc) {}
	~InitMushroomEvent() {}

	Vector2D getInitLoc() const { return mInitLoc; }
private:
	Vector2D mInitLoc;
};
#endif