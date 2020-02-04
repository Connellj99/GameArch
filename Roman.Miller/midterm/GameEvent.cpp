#include "GameEvent.h"

CreateFoodEvent::CreateFoodEvent(const Vector2D & loc)
	:Event((EventType)CREATE_FOOD)
{
}

CreateFoodEvent::~CreateFoodEvent()
{
}

DestroyFoodEvent::DestroyFoodEvent(const Vector2D & loc)
	:Event((EventType)DESTROY_FOOD)
{
}

DestroyFoodEvent::~DestroyFoodEvent()
{
}

DestroyPowerEvent::DestroyPowerEvent()
	:Event((EventType)DRESTROY_POWERUP)
{
}

DestroyPowerEvent::~DestroyPowerEvent()
{
}

CreatePowerEvent::CreatePowerEvent()
	:Event((EventType)CREATE_POWERUP)
{
}

CreatePowerEvent::~CreatePowerEvent()
{
}