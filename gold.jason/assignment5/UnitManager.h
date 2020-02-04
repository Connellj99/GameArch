#ifndef UnitManager_h
#define UnitManager_h

#include "Trackable.h"
#include <vector>
#include "Unit.h"

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();
	void addUnit(float posX, float posY, float scale, std::vector<Sprites*> animationvector);
	void removeUnit(float clickedX, float clickedY);
	void cleanUp();
	void updateAll(double looptime);
	void drawAll();
	void setAnimationAll();
	bool isOverSprites(float clickedX, float clickedY);
	Unit* getCurrentUnit()
	{
		return mpCurrentUnit;
	};
private:
	std::vector<Unit*> mUnitHolder;
	Unit* mpCurrentUnit;
	int mCurrentAnimationSetting = 0;
};
#endif // !UnitManager_h
