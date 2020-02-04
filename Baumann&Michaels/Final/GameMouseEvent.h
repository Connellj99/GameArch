#pragma once
#ifndef GAME_MOUSE_EVENT_H
#define GAME_MOUSE_EVENT_H

#include "MouseEvent.h"

class GameMouseEvent :public Event 
{
private:
	Vector2D mLoc;
	MouseButtonType mbType;

public:


	GameMouseEvent(const Vector2D& loc, const MouseButtonType& mb);
	~GameMouseEvent();

	Vector2D getLocation() const { return mLoc; }
	MouseButtonType getButtonType() const { return mbType; }
};

#endif