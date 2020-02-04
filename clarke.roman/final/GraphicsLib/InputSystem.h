#ifndef  INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include  "Trackable.h"
#include <allegro5/events.h>

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();
	void update(float curTime);
private:
	InputSystem(const InputSystem&) = delete;
	void operator=(const InputSystem&) = delete;

	bool mIsInitted = false;

	ALLEGRO_EVENT_QUEUE* mpEventQueue;
};
#endif