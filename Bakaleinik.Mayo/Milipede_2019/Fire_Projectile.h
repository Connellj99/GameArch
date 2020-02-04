#pragma once
#include "Event.h"
#include "GameEvent.h"

class Fire_Projectile : public Event
{
public:
	Fire_Projectile() :Event((EventType)FIRE) {};
	~Fire_Projectile() {};
};