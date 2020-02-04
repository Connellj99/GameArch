#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "Unit.h"
#include "EventListener.h"
#include "GraphicsBufferManager.h"

// holds a list of all Units in the game
class UnitManager : public EventListener
{
public:
	UnitManager(GraphicsBufferManager* graphicsBUfferManager);
	~UnitManager();

	void init();
	void cleanup() override;
	void handleEvent(const Event& theEvent) override;

	// create smurf unit at left mouse click
	void initSmurf(const Vector2D& spawnLoc);
	// delete smurfs at right mouse click
	void destroyUnitsAtLoc(const Vector2D& atLoc);
	// switch most recent smurf unit's animation when enter key is down
	void swapSmurfAnimation();
	// toggle all smurfs' animations on Space
	void toggleAnimations();

	// remove and delete all units
	void clear();
	void update(float curTime);
	void draw();
private:
	GraphicsBufferManager* mpGraphicsBufferManager;
	std::vector<Unit*> mUnits;

	Unit* createUnit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale);
	std::vector<bool> getUnitsAtLoc(const Vector2D& atLoc);

	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";

	// smurf config
	const std::string SMURFS_FILENAME = "smurf_sprites.png";
	const std::string DEAN_SMURFS_FILENAME = "dean_sprites.png";
	const BufferKey SMURF_BUFFER_KEY = "SMURF";
	const BufferKey DEAN_SMURF_BUFFER_KEY = "DEAN";
	const Vector2D SMURF_SPRITE_SIZE = Vector2D(60, 60);
	const AnimKey SMURF_ANIMATION_NAME = "SMURF";
	const AnimKey DEAN_SMURF_ANIMATION_NAME = "DEAN";
	const float SMURF_ANIMATION_SPEED_INIT = 0.5f;
	//const float SMURF_ANIMATION_SPEED_INCREMENT = 0.01f;
	const Vector2D SMURF_SCALE = Vector2D(1, 1);

	// most recently created smurf unit
	Unit* mpCurSmurfUnit = nullptr;
	// true is smurf anim is dean anim, false if normal smurf anim
	bool mAnimIsDean = false;
};
#endif