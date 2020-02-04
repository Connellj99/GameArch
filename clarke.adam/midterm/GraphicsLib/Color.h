#ifndef COLOR_H
#define COLOR_H

#include "Trackable.h"

struct Color : public Trackable
{
public:
	Color(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a) {}

	float r, g, b, a;
private:
	ALLEGRO_COLOR getAllegroColor() const { return al_map_rgba(r, g, b, a); }

	friend class GraphicsSystem;
	friend class GraphicsBuffer;
};
#endif