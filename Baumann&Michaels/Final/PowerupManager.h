#pragma once
#ifndef POWERUP_MANAGER_H
#define POWERUP_MANAGER_H

#include "Trackable.h"
#include "UnitManager.h"
#include "Powerup.h"
#include <Random>
#include <vector>

class PowerupManager :public Trackable
{
private:
	vector<Powerup*> mPowerupList;
	vector<Powerup*> mPowerupToSpawnList;
	UnitManager* manager;
	int powerupCollisionOffset;
	int screenWidth;
	int screenHeight;
	int screenPadding;
	double timeToSpawn;
	double maxPowerupTime;
	PowerupManager();
public:
	PowerupManager(UnitManager* newManager, int offset, int newScreenWidth, int newScreenHeight, int newScreenPadding);
	void addPowerupToGame(string powerup);
	void addPowerupToBuffer(Powerup* powerup);
	void checkAllPowerupsForCollisionWithPlayer();
	void updatePowerupSpawning(double deltaTime);
	void removePowerupFromGame(string powerupName);
	void removeAllPowerupsFromGame();
	bool checkPowerupInGame(Powerup* powerup);
	Powerup* getPowerup(string name);
	void setMaxPowerupTime(double time);
	void incrementPlayerLength();

	~PowerupManager();
};

#endif