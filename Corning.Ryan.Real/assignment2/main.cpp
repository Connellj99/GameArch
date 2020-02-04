#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsLib.h>

using namespace std;

int main()
{
	initAllegro();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	//
	return 0;

}