#ifndef MUSHROOM_UNIT_MANAGER_H
#define MUSHROOM_UNIT_MANAGER_H

#include "MushroomUnit.h"
#include <vector>
#include "EventListener.h"

class MushroomUnitManager : public EventListener
{
public:
	MushroomUnitManager();
	~MushroomUnitManager();

	void init();
	void reset();
	void cleanup() override;
	void handleEvent(const Event& theEvent) override;

	bool intersectsAny(const Vector2D& atLoc);

	void physicsUpdate(float curTime);
	void update(float curTime);
	void draw();
private:
	std::vector<MushroomUnit*> mMushroomUnits;

	Vector2D getRandLoc();
	void clear();
};
#endif
