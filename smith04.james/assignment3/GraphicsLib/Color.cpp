#include "Color.h"

Color::Color()
{
	r = g = b = 0;
}

Color::Color(int red, int green, int blue)
{
	if (red > 255)
		r = 255;
	else if (red < 0)
		r = 0;
	else
		r = red;

	if (green > 255)
		g = 255;
	else if (green < 0)
		g = 0;
	else
		g = green;

	if (blue > 255)
		b = 255;
	else if (blue < 0)
		b = 0;
	else
		b = blue;

	mColor = al_map_rgb(r, g, b);
}

void Color::setR(int red)
{
	if (red > 255)
		r = 255;
	else if (red < 0)
		r = 0;
	else
		r = red;

	mColor = al_map_rgb(r, g, b);
}

void Color::setG(int green)
{
	if (green > 255)
		g = 255;
	else if (green < 0)
		g = 0;
	else
		g = green;

	mColor = al_map_rgb(r, g, b);
}

void Color::setB(int blue)
{
	if (blue > 255)
		b = 255;
	else if (blue < 0)
		b = 0;
	else
		b = blue;
	
	mColor = al_map_rgb(r, g, b);
}

ALLEGRO_COLOR Color::getColor()
{
	return mColor;
}