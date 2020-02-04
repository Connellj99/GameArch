/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Midterm
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "LevelManager.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{
	cleanup();
}

void LevelManager::cleanup()
{
	int size = mvCollection.size();
	for (int i = 0; i < size; i++)
	{
		delete mvCollection[i];
	}

	mvCollection.clear();
}

void LevelManager::init(int numLevels)
{
	int levelsToAdd = numLevels;
	string filename;
	for (int i = 0; i < levelsToAdd; i++)
	{
		if (i == 0)
		{
			filename = "Level1.txt";
		}
		if (i == 1)
		{
			filename = "Level2.txt";
		}
		if (i == 2)
		{
			filename = "Level3.txt";
		}
		mvCollection.push_back(new Level(filename));
	}
}

Level * LevelManager::getLevel(int levelNum)
{
	int index = levelNum - 1;
	return mvCollection[index];
}