#ifndef CENTIPEDE_MANAGER_H
#define CENTIPEDE_MANAGER_H

#include <vector>
#include "CentipedeUnit.h"
#include "EventListener.h"

class CentipedeManager : public EventListener
{
public:
	CentipedeManager();
	~CentipedeManager() { CentipedeManager::cleanup(); }

	void init();
	void reset();
	void cleanup() override;
	void respawn(bool doIncrementSpeed);
	void physicsUpdate(float curTime);
	void update(float curTime);
	void draw();
	void handleEvent(const Event& theEvent) override;
private:
	std::vector<CentipedeUnit*> mCentipedeUnits{};
	int mNumSegmentsLeft = 0;
};
#endif