#include "Color.h"

// This constructor initializes the color based on the red,
// green, blue values given by the user
Color::Color(float r, float g, float b)
{
	mCurrentColor = al_map_rgb(r, g, b);
}





// This constructor initializes the color based on the red,
// green, blue, and alpha values given by the user
Color::Color(float r, float g, float b, float a)
{
	mCurrentColor = al_map_rgba(r, g, b, a);
}





// The destructor for the color class
Color::~Color()
{
}