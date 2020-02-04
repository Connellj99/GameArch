#include <map>
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

#include "Trackable.h"

#include "UnitTypes.h"

#include "BufferFlags.h"
#include "FontFlags.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GraphicsSystem.h"

#include "Level.h"
#include "LevelManager.h"



LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}

void LevelManager::cleanUp()
{
	clear();

	return;
}

void LevelManager::update(double _deltaTime)
{


}

void LevelManager::addLevel(LevelKey _key, Level* _pLevel)
{
	mmLevels.insert(std::pair<LevelKey, Level*>(_key, _pLevel));

	return;
}

Level* LevelManager::getLevel()
{
	return mmLevels[mCurrentLevel];
}

bool LevelManager::getLevel(LevelKey _key, Level* _pLevel)
{
	std::map<LevelKey, Level*>::iterator it = mmLevels.find(_key);

	if (it != mmLevels.end())
	{
		_pLevel = it->second;
		return true;
	}
	return false;
}

bool LevelManager::getLevel(LevelKey _key)
{
	if (mCurrentLevel == _key)
	{
		return true;
	}

	return false;
	
}

void LevelManager::setLevel(LevelKey _key)
{
	std::map<LevelKey, Level*>::iterator iterator = mmLevels.find(_key);

	// Make sure the level exists before setting it.
	if (iterator != mmLevels.end())
	{
		mCurrentLevel = iterator->first;
	}

	return;
}

void LevelManager::draw(GraphicsSystem * _pGraphicsSystem)
{
	mmLevels[mCurrentLevel]->draw(_pGraphicsSystem);
	return;
}

void LevelManager::swapLevel()
{
	if (mCurrentLevel == "Level 1")
	{
		mCurrentLevel = "Level 2";
	}
	else
	{
		mCurrentLevel = "Level 1";
	}

	return;
}

void LevelManager::clear()
{
	if (!mmLevels.empty())
	{
		for (std::multimap<LevelKey, Level*>::iterator iterator = mmLevels.begin(); iterator != mmLevels.end(); iterator++)
		{
			delete iterator->second;

			iterator->second = nullptr;
		}
	}

	mmLevels.clear();

	return;
}

bool LevelManager::checkPLayerSize(int _currentSize)
{
	if (mmLevels[mCurrentLevel]->getPlayerEndLength() == _currentSize)
	{
		changeLevel();
		return true;
	}

	return false;
}

void LevelManager::drawHUD(GraphicsSystem * _pGraphicsSystem, int _score, Font& _font, Color& _color)
{
	if (mCurrentLevel != "Main Menu" && mCurrentLevel != "Game Over")
	{
		size_t levelNumber = mCurrentLevel.find("Level ");
		
		std::string number = std::string(1, mCurrentLevel[levelNumber + 6]);

		_pGraphicsSystem->writeText(40, 40, _font, _color, "Level:" + number + " Score:" + std::to_string(_score));
	}
	else
	{
		_pGraphicsSystem->writeText(_pGraphicsSystem->getWidth() / 2, _pGraphicsSystem->getHeight() * 0.75, _font, _color, "Press 'SPACE' to continue.", FONT_ALIGN_CENTER);
	}

	return;
}

void LevelManager::changeLevel()
{
	if (mCurrentLevel == "Main Menu")
	{
		mCurrentLevel = "Level 1";
		return;
	}
	else if (mCurrentLevel == "Game Over")
	{
		mCurrentLevel = "Main Menu";
		return;
	}
	else
	{
		bool foundCurrentLevel = false;

		for (std::map<LevelKey, Level*>::iterator iterator = mmLevels.begin(); iterator != mmLevels.end(); iterator++)
		{
			if (foundCurrentLevel && iterator->first.find("Level") != std::string::npos)
			{
				mCurrentLevel = iterator->first;
				return;
			}

			if (iterator->first == mCurrentLevel)
			{
				foundCurrentLevel = true;
			}
		}

		mCurrentLevel = "Game Over";
	}

	return;
}

void LevelManager::changeLevel(LevelKey _level)
{
	std::map<LevelKey, Level*>::iterator iterator = mmLevels.find(_level);

	if (iterator != mmLevels.end())
	{
		mCurrentLevel = _level;
	}

	return;
}
