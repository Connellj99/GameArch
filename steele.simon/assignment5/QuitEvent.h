#ifndef QUITEVENT_H
#define QUITEVENT_H

// Local includes
#include "GameEvent.h"


class QuitEvent : public Event
{
public:

	// Constructors
	QuitEvent() :Event((EventType)QUIT_GAME) {};

	// Destructors
	~QuitEvent() {};

private:
};

#endif // !QUITEVENT_H

