#include "LevelManager.h"


LevelManager* LevelManager::mpsLevelManager = nullptr;

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
	clear();
}

LevelManager * LevelManager::getInstance()
{
	return mpsLevelManager;
}

void LevelManager::initInstance()
{
	if (mpsLevelManager == nullptr)
	{
		mpsLevelManager = new LevelManager();
	}
}

void LevelManager::cleanupInstance()
{
	delete mpsLevelManager;
}

//cleans up the level map
void LevelManager::clear()
{
	std::map<Key, LevelOutline*>::iterator itr;
	for (itr = mLevelMap.begin(); itr != mLevelMap.end(); itr++)
	{
		LevelOutline* pLevelOutline = itr->second;
		delete pLevelOutline;
	}
	mLevelMap.clear();
}

//adds a level to the map and adds it to the level order
void LevelManager::addLevel(std::string key, LevelOutline * level)
{
	mLevelMap.insert(std::pair<Key, LevelOutline*>(key, level));
	mLevelOrder.push_back(key);
}

//loads the level based on the key to allow for level select
void LevelManager::startLevel(std::string key)
{
	std::vector<std::string>::iterator itr = std::find(mLevelOrder.begin(), mLevelOrder.end(), key);//mLevelMap.find(key);
	mCurrentIndex = std::distance(mLevelOrder.begin(), itr);
	if (key == "start") 
	{
		mCurrentIndex = 0;
	}
	mLevelMap[mLevelOrder[mCurrentIndex]]->reset();
}

//loads the next level
void LevelManager::startNextLevel()
{
	mCurrentIndex++;
}

//getter for current level
LevelOutline * LevelManager::getLevel()
{
	return mLevelMap[mLevelOrder[mCurrentIndex]];
}

void LevelManager::init() 
{
}
