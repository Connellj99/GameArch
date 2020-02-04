#include "Color.h"

Color::Color()
{
	mColor = al_map_rgba(0, 0, 0, 0);
}

Color::Color(int rValue, int gValue, int bValue, int aValue)
{
	mColor = al_map_rgba(rValue, gValue, bValue, aValue);
}
//axcessor for color instead of 4 for each chanel
ALLEGRO_COLOR Color::getColor()
{
	return mColor;
}