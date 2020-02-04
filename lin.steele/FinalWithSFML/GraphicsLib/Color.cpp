#include "Color.h"

Colors::Colors()
{
	sf::Color(white);
}

// This constructor initializes the color based on the red,
// green, blue values given by the user
Colors::Colors(float r, float g, float b)
{
	//mCurrentColor = al_map_rgb(r, g, b);
}





// This constructor initializes the color based on the red,
// green, blue, and alpha values given by the user
Colors::Colors(float r, float g, float b, float a)
{
	//mCurrentColor = al_map_rgba(r, g, b, a);
}







// The destructor for the color class
Colors::~Colors()
{
}





// This function sets the R value of the current color
void Colors::setR(float newR) 
{
	//mCurrentColor.r = newR;
}





// This function sets the G value of the current color
void Colors::setG(float newG)
{
	//mCurrentColor.g = newG;
}





// This function sets the B value of the current color
void Colors::setB(float newB)
{
	//mCurrentColor.b = newB;
}