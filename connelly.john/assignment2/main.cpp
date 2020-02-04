//John Connelly
/*

Program Functionality
• Create and init a GraphicsSystem object – 800x600 windowed
• Create 3 GraphicsBuffers – one containing the steps.png image, one containing
smurf_sprites.png, and the other completely red (800x600) – make sure the Red one is created
in memory – not read in from a file!
• Fill the red buffer with the words “Curse you Papa Smurf!” in black. – make sure this is done
using the GraphicsSystem::writeText function which writes to a target graphics buffer
• Draw the all red buffer – then scale down the steps.png buffer by 1/3 when drawing. – Center
the woods inside the Red buffer
• Create 16 Sprites from the smurf_sprites buffer – display all 16 of them at random positions
(different random positions for each one)
• Save the BackBuffer to a file (backbuffer.jpg) using GraphicsSystem::saveBuffer function
• Save the RedBuffer (with text) to a file (redbuffer.jpg) using GraphicsSystem::saveBuffer
function
• Flip the Graphics System
• After 5 seconds – close down the application (gracefully).

*/
#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsLib.h>
#include "GraphicsHeaders.h"
#include "GraphicsLib.cpp"

using namespace std;

int main()
{
	initAllegro();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}