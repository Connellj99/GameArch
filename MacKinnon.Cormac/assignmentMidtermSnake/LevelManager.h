#pragma once
#include "LevelCreation.h"
#include "LevelOutline.h"
#include "StartLevel.h"
#include "EndLevel.h"
#include <vector>
#include <map>
#include "Trackable.h"

class LevelOutline;

class LevelManager : public Trackable
{
public:
	LevelManager();
	~LevelManager();

	static LevelManager* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init();
	void clear();

	void addLevel(std::string key, LevelOutline* level);

	void startLevel(std::string key);
	void startNextLevel();

	LevelOutline* getLevel();

private:
	static LevelManager* mpsLevelManager;

	std::map<Key, LevelOutline*> mLevelMap;
	std::vector<std::string> mLevelOrder;
	unsigned int mCurrentIndex;
};

