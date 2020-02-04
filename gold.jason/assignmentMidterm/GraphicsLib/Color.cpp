#include "Color.h"

Color::Color()
{
	mCol = al_map_rgb(0, 0, 0);
}


Color::Color(int r, int g, int b)
{
	mCol = al_map_rgb(r, g, b);
}

Color::~Color()
{
}