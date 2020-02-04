#include "GameEvent.h"


DestroyEvent::DestroyEvent(const Vector2D & loc)
	:Event((EventType)DESTROY),
	mLoc(loc)
{
}

DestroyEvent::~DestroyEvent()
{
}

UnitEvent::UnitEvent(const Vector2D & loc)
	:Event((EventType)CREATE)
	, mLoc(loc)
{
}
UnitEvent::~UnitEvent()
{
}