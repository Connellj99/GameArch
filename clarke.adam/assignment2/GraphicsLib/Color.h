#ifndef COLOR_H
#define COLOR_H

#include "Trackable.h"

struct Color : public Trackable
{
	Color(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a) {}

	ALLEGRO_COLOR getAllegroColor() const
	{
		return al_map_rgba(r, g, b, a);
	}

	float r, g, b, a;
};
#endif