/*
Animation
A class to hold a list of Sprites and the timing information to switch between them
Data
• A “list” of Sprites
• Timing info
• Data to keep track of which Sprite is current
• Data to indicate if animation should loop (start at beginning of list after reaching end) or not
Functions
• Constructor(s)/destructor
• Some way of getting Sprite’s into Animation either through constructor or an addSprite function
• Update – figure out what Sprite is “current” 
• getCurrentSprite()
• speed up/slow down – adjust timing to make animation faster or slower
*/

#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{
	
}