#include "Colors.h"

//constructor that takes the passed in rgb values and creates a new allegro color and sets it to the mColor pointer
Colors::Colors(float r, float g, float b)
{
	mColor = new ALLEGRO_COLOR(al_map_rgb(r, g, b));
}

Colors::~Colors()
{
	//stub
	//did not find a destroy color
}
