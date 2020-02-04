#include "GameMouseEvent.h"

GameMouseEvent::GameMouseEvent(const Vector2D& loc, const MouseButtonType& mb)
	: Event(GAME_MOUSE_CHANGED), mLoc(loc), mbType(mb)
{
}

GameMouseEvent::~GameMouseEvent()
{
}