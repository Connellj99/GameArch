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


	// Friends
	friend class GraphicsBuffer;
	friend class GraphicsSystem;

	// Constructors
	Color( float r, float g, float b );
	Color( float r, float g, float b, float a );

	// Destructor
	~Color();


private:

	// Allegro Color
	ALLEGRO_COLOR  mCurrentColor;
};

#endif