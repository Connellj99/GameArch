#include "Font.h"

//load font from path constuctor
Font::Font(const string assetPath, const string filename, int size)
{
	mpFont = al_load_ttf_font((assetPath + filename).c_str(), size, 0);
	assert(mpFont);
	mSize = size;
}
//delete font destuctor
Font::~Font()
{
	al_destroy_font(mpFont);
}
//return size
int Font::getSize()
{
	return mSize;
}
//return font pointer
ALLEGRO_FONT * Font::getFont()
{
	return mpFont;
}
