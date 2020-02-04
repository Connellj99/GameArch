#include "PlayerUnit.h"
#include "GameEvent.h"
#include "EventSystem.h"

PlayerUnit::PlayerUnit(std::map<std::string, Animation>& animations,
	const Vector2D& initLoc, const Vector2D& scale)
	:Unit(animations, initLoc, scale)
{
	EventSystem::getInstance()->addListener(EventType(PLAYER_SWAP_DIR_EVENT), this);
}

PlayerUnit::~PlayerUnit()
{

}

void PlayerUnit::update(float curTime)
{
	Unit::update(curTime);

	auto loc = getLocation();
	if(loc.getX() < 600 && loc.getX() > 0)
	{
		loc.setX(loc.getX() + mXMovDir * mMoveSpeed);
		setLocation(loc);
	}
}


void PlayerUnit::handleEvent(const Event& theEvent)
{
	if(theEvent.getType() == EventType(PLAYER_SWAP_DIR_EVENT))
	{
		mXMovDir *= -1;
	}
}