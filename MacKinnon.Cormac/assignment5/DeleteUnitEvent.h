#pragma once
#include "Event.h"
#include "Vector2D.h"

class DeleteUnitEvent : public Event
{
public:
	DeleteUnitEvent(Vector2D pos);
	~DeleteUnitEvent();

	Vector2D getMousePos() const;

private:
	Vector2D mMousePos;
};

