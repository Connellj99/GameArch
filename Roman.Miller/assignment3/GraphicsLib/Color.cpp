#include "Color.h"


Color::Color()
{
	mColor = al_map_rgba(0, 0, 0, 0);
}

Color::Color(int r, int g, int b, int a)
{
	mColor = al_map_rgba(r, g, b, a);
}
//acessor 
ALLEGRO_COLOR Color::getColor()
{
	return mColor;
}