#ifndef SHOOTEVENT_H
#define SHOOTEVENT_H

// Local includes
#include "GameEvent.h"


class ShootBulletEvent : public Event
{
public:

	// Constructors
	ShootBulletEvent() :Event((EventType)SHOOT_BULLET) {};

	// Destructors
	~ShootBulletEvent() {};

private:
};

#endif // !SHOOTEVENT_H
