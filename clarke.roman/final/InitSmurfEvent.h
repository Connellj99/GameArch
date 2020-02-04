#ifndef SPAWN_SMURF_EVENT_H
#define SPAWN_SMURF_EVENT_H

#include "Event.h"
#include "GameEvent.h"
#include "Vector2D.h"

class InitSmurfEvent : public Event
{
public:
	InitSmurfEvent(const Vector2D& spawnLoc) : Event(EventType(INIT_SMURF_EVENT)),
		mSpawnLoc(spawnLoc) {}
	~InitSmurfEvent() {}

	Vector2D getSpawnLoc() const { return mSpawnLoc; }
private:
	Vector2D mSpawnLoc;
};
#endif