#include "MouseClickEvent.h"



MouseClickEvent::MouseClickEvent(int mouseValue, int x, int y) 
	: Event(MOUSE_PRESS_EVENT)
{
	mPressedButton = mouseValue;
	mMousePos = Vector2D(x, y);
}

MouseClickEvent::~MouseClickEvent()
{
}

int MouseClickEvent::getPressedbutton() const
{
	return mPressedButton;
}

Vector2D MouseClickEvent::getMousePos() const
{
	return mMousePos;
}
