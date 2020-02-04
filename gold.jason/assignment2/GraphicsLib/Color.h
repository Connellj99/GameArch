#pragma once

#include "GraphicsLib.h"

class Color : public Trackable
{
private:

	ALLEGRO_COLOR mColor;

public:

	//getter
	ALLEGRO_COLOR getColor();

	//constructors
	Color();
	Color(int, int, int);
	Color(int, int, int, int);

	//destructor
	~Color();
};