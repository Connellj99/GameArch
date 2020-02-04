#ifndef DELETE_SMURF_EVENT_H
#define DELETE_SMURF_EVENT_H

#include "Event.h"
#include "GameEvent.h"
#include "Vector2D.h"

class DestroySmurfEvent : public Event
{
public:
	DestroySmurfEvent(const Vector2D& atLoc) : Event(EventType(DESTROY_SMURF_EVENT)),
		mDeleteLoc(atLoc) {}
	~DestroySmurfEvent() {}

	Vector2D getDeleteLoc() const { return mDeleteLoc; }
private:
	Vector2D mDeleteLoc;
};
#endif