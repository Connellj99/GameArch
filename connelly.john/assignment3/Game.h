#ifndef GAME_H
#define GAME_H

#include "Trackable.h"
#include "System.h"
#include "PerformanceTracker.h"
#include "Unit.h"

/*
Game
The class which holds all systems and has the game loop
Data
• The System object
• Other data necessary to fulfill the requirements of the assignment
Public Functions
• Constructor/Destructor
• Init/Cleanup
• DoLoop – things to do not necessarily in this order:
o Get user input
o Adjust game state (based on user input and other automatic factors)
*/

class Game : public Trackable
{
public:
	Game();
	~Game();

	void initialize();
private:
	//system object
	//other data necessary
};

#endif