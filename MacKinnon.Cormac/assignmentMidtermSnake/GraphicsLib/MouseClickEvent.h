#pragma once
#include "Event.h"
#include "Vector2D.h"

class MouseClickEvent : public Event
{
public:
	MouseClickEvent(int mouseValue, int x, int y);
	~MouseClickEvent();

	int getPressedbutton() const;
	Vector2D getMousePos() const;

private:
	int mPressedButton;
	Vector2D mMousePos;

};

