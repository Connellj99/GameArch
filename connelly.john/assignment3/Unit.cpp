/*
A class to hold state information for a game entity – for now, it holds location info for an animation
Data
• location (x,y)
• animation(s)
Functions
• constructor(s)/destructor
• update – adjusts the state of the Unit – in this case at minimum will call animation’s update
function
• draw – draw the current animation’s current sprite in the location of the unit
• setAnimation – switch to a new animation 
*/

#include "Unit.h"
#include "Game.h"

Unit::Unit()
{
	
}

Unit::~Unit()
{
}