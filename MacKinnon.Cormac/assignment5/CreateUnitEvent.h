#pragma once
#include "Event.h"
#include "Vector2D.h"

class CreateUnitEvent : public Event
{
public:
	CreateUnitEvent(Vector2D pos);
	~CreateUnitEvent();

	Vector2D getMousePos() const;

private:
	Vector2D mMousePos;
};

