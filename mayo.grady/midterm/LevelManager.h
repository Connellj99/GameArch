#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Midterm
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include <vector>
#include "Level.h"

class Level;

class LevelManager : public Trackable
{
private:
	//collection of Levels
	std::vector<Level*> mvCollection;

public:
	//constructor & destructor
	LevelManager();
	~LevelManager();

	//cleanup
	void cleanup();

	//init
	void init(int numLevels);

	Level * getLevel(int levelNum);
};