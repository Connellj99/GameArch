#pragma once
#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include <Vector2D.h>
#include "Event.h"

enum MouseButtonType { INVALID_MB_TYPE = -1, LEFT_MOUSE, RIGHT_MOUSE, MOUSE_OVER, NUM_MB_TYPES };

class MouseEvent :public Event 
{
private:
	Vector2D mLoc;
	MouseButtonType mbType;

public:
	

	MouseEvent(const Vector2D& loc, const MouseButtonType& mb);
	~MouseEvent();

	Vector2D getLocation() const { return mLoc; }
	MouseButtonType getButtonType() const { return mbType; }
};

#endif