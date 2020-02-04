#pragma once
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <allegro5/events.h>

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();
	void update(double time);

private:
	ALLEGRO_EVENT_QUEUE* mpEventQueue;

	bool mIsInit;
};

