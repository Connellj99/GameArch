#ifndef COLOR_H
#define COLOR_H

#include <allegro5\allegro_color.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

using namespace std;

class Color : public Trackable
{
public:
	friend class GraphicsBuffer;
	friend class GraphicsSystem;
	Color();
	~Color();


private:

	ALLEGRO_COLOR  mCurrentColor;
};

#endif