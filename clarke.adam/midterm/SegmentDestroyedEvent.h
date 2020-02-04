#ifndef SEGMENT_DESTROYED_EVENT_H
#define SEGMENT_DESTROYED_EVENT_H

#include "GameEvent.h"

class SegmentDestroyedEvent : public Event
{
public:
	SegmentDestroyedEvent(int points)
		: Event(EventType(SEGMENT_DESTROYED_EVENT)), mPoints(points)
	{}
	~SegmentDestroyedEvent() {}

	int getPoints() const { return mPoints; }
private:
	int mPoints;
};
#endif