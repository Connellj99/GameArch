#ifndef MOVE_PLAYER_EVENT_H
#define MOVE_PLAYER_EVENT_H

#include "Event.h"
#include "GameEvent.h"
#include "Vector2D.h"

class PlayerMoveEvent : public Event
{
public:
	PlayerMoveEvent(const Vector2D& newLoc, float curTime) : Event(EventType(PLAYER_MOVE_EVENT)),
		mNewLoc(newLoc), mCurTime(curTime) {}
	~PlayerMoveEvent() {}

	Vector2D getNewLoc() const { return mNewLoc; }
	float getCurTime() const { return mCurTime; }
private:
	Vector2D mNewLoc;
	float mCurTime;
};
#endif